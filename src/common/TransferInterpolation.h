#if 0
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

/**********************************************************
 * Safe bilinear sampling
 **********************************************************/
inline float bilinear(const std::vector<float>& img,
                      int w, int h,
                      float x, float y)
{
    x = std::clamp(x, 0.0f, float(w - 1));
    y = std::clamp(y, 0.0f, float(h - 1));

    int x0 = int(std::floor(x));
    int y0 = int(std::floor(y));
    int x1 = std::min(x0 + 1, w - 1);
    int y1 = std::min(y0 + 1, h - 1);

    float dx = x - x0;
    float dy = y - y0;

    float v00 = img[y0*w + x0];
    float v01 = img[y1*w + x0];
    float v10 = img[y0*w + x1];
    float v11 = img[y1*w + x1];

    float v0 = v00*(1 - dy) + v01*dy;
    float v1 = v10*(1 - dy) + v11*dy;

    return v0*(1 - dx) + v1*dx;
}


/**********************************************************
 * Separable Gaussian blur (5-tap)
 **********************************************************/
std::vector<float> gaussian_separable(
        const std::vector<float>& src,
        int w, int h)
{
    static const float k[5] = {1/16.f, 4/16.f, 6/16.f, 4/16.f, 1/16.f};

    std::vector<float> tmp(w*h);
    std::vector<float> dst(w*h);

    // Horizontal
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            float sum = 0;
            for (int t = -2; t <= 2; t++)
            {
                int xx = std::clamp(x + t, 0, w - 1);
                sum += src[y*w + xx] * k[t + 2];
            }
            tmp[y*w + x] = sum;
        }

    // Vertical
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            float sum = 0;
            for (int t = -2; t <= 2; t++)
            {
                int yy = std::clamp(y + t, 0, h - 1);
                sum += tmp[yy*w + x] * k[t + 2];
            }
            dst[y*w + x] = sum;
        }

    return dst;
}


/**********************************************************
 * Downsample 2x with blur
 **********************************************************/
std::vector<float> downsample2(const std::vector<float>& src,
                               int w, int h,
                               int& outW, int& outH)
{
    auto tmp = gaussian_separable(src, w, h);

    outW = w / 2;
    outH = h / 2;

    std::vector<float> dst(outW*outH);

    for (int y = 0; y < outH; y++)
        for (int x = 0; x < outW; x++)
            dst[y*outW + x] = tmp[(y*2)*w + (x*2)];

    return dst;
}


/**********************************************************
 * Flow field container
 **********************************************************/
struct FlowField {
    int w = 0, h = 0;
    std::vector<float> u;
    std::vector<float> v;
};


/**********************************************************
 * Horn–Schunck iteration (single level)
 **********************************************************/
void horn_schunck_level(
        const std::vector<float>& A,
        const std::vector<float>& B,
        int w, int h,
        std::vector<float>& u,
        std::vector<float>& v,
        float alpha = 15.0f,
        int iterations = 100)
{
    const int N = w*h;

    std::vector<float> Ix(N), Iy(N), It(N);

    // Compute gradients (safe boundaries)
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            int i = y*w + x;

            int xm = std::max(x - 1, 0);
            int xp = std::min(x + 1, w - 1);
            int ym = std::max(y - 1, 0);
            int yp = std::min(y + 1, h - 1);

            Ix[i] = 0.5f * ((A[y*w + xp] - A[y*w + xm]) +
                            (B[y*w + xp] - B[y*w + xm]));

            Iy[i] = 0.5f * ((A[yp*w + x] - A[ym*w + x]) +
                            (B[yp*w + x] - B[ym*w + x]));

            It[i] = B[i] - A[i];
        }

    std::vector<float> u_new(N), v_new(N);
    float a2 = alpha*alpha;

    for (int it = 0; it < iterations; it++)
    {
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
            {
                int i = y*w + x;

                float us = 0, vs = 0;
                int c = 0;

                if (x > 0)     { us += u[i - 1]; vs += v[i - 1]; c++; }
                if (x < w - 1) { us += u[i + 1]; vs += v[i + 1]; c++; }
                if (y > 0)     { us += u[i - w]; vs += v[i - w]; c++; }
                if (y < h - 1) { us += u[i + w]; vs += v[i + w]; c++; }

                float u_avg = (c ? us / c : u[i]);
                float v_avg = (c ? vs / c : v[i]);

                float P = Ix[i]*u_avg + Iy[i]*v_avg + It[i];
                float D = a2 + Ix[i]*Ix[i] + Iy[i]*Iy[i];

                u_new[i] = u_avg - Ix[i]*P/D;
                v_new[i] = v_avg - Iy[i]*P/D;
            }

        u.swap(u_new);
        v.swap(v_new);
    }
}


/**********************************************************
 * Pyramid
 **********************************************************/
struct Pyramid {
    std::vector<std::vector<float>> level;
    std::vector<int> W, H;
};

Pyramid build_pyramid(const std::vector<float>& base,
                      int w, int h, int levels)
{
    Pyramid P;
    P.level.push_back(base);
    P.W.push_back(w);
    P.H.push_back(h);

    for (int i = 1; i < levels; i++)
    {
        int nw, nh;
        auto ds = downsample2(P.level.back(), P.W.back(), P.H.back(), nw, nh);
        P.level.push_back(std::move(ds));
        P.W.push_back(nw);
        P.H.push_back(nh);
    }
    return P;
}


/**********************************************************
 * Flow upscale 2×
 **********************************************************/
void upscale_flow(FlowField &F, int newW, int newH)
{
    std::vector<float> u2(newW * newH);
    std::vector<float> v2(newW * newH);

    for (int y = 0; y < newH; y++)
        for (int x = 0; x < newW; x++)
        {
            float fx = x / 2.0f;
            float fy = y / 2.0f;

            u2[y*newW + x] = bilinear(F.u, F.w, F.h, fx, fy) * 2.0f;
            v2[y*newW + x] = bilinear(F.v, F.w, F.h, fx, fy) * 2.0f;
        }

    F.w = newW;
    F.h = newH;
    F.u.swap(u2);
    F.v.swap(v2);
}


/**********************************************************
 * Safe warp: uses explicit w,h (NOT flow's!)
 **********************************************************/
std::vector<float> warp_with_flow(
        const std::vector<float> &A,
        int w, int h,
        const FlowField &flow,
        float t)
{
    // Safety: must match
    if (flow.u.size() != A.size()) {
        printf("ERROR: warp dimension mismatch A=%zu flow=%zu\n",
               A.size(), flow.u.size());
        abort();
    }

    std::vector<float> out(w * h);

    for (int i = 0; i < w*h; i++)
    {
        int x = i % w;
        int y = i / w;

        float nx = x + flow.u[i] * t;
        float ny = y + flow.v[i] * t;

        out[i] = bilinear(A, w, h, nx, ny);
    }

    return out;
}


/**********************************************************
 * Full pyramid Horn–Schunck
 **********************************************************/
FlowField pyramid_optical_flow(
        const std::vector<float> &A,
        const std::vector<float> &B,
        int w, int h,
        int levels = 4)
{
    Pyramid PA = build_pyramid(A, w, h, levels);
    Pyramid PB = build_pyramid(B, w, h, levels);

    FlowField F;
    int L = levels - 1;

    F.w = PA.W[L];
    F.h = PA.H[L];
    F.u.assign(F.w * F.h, 0);
    F.v.assign(F.w * F.h, 0);

    for (int lvl = L; lvl >= 0; lvl--)
    {
        if (lvl != L)
            upscale_flow(F, PA.W[lvl], PA.H[lvl]);

        auto Awarp = warp_with_flow(PA.level[lvl], PA.W[lvl], PA.H[lvl],
                                    F, 1.0f);

        horn_schunck_level(Awarp, PB.level[lvl],
                           PA.W[lvl], PA.H[lvl],
                           F.u, F.v,
                           15.0f,
                           (lvl == 0 ? 150 : 100));
    }

    return F;
}


/**********************************************************
 * High-level interpolation API
 **********************************************************/
std::vector<float> transferInterpolation(
        const std::vector<float> &A,
        const std::vector<float> &B,
        int w, int h,
        float t)
{
    FlowField F = pyramid_optical_flow(A, B, w, h, 4);
    return warp_with_flow(A, w, h, F, t);
}


#endif

#if 0
#include <vector>
#include <cmath>
#include <algorithm>

/**********************************************************
 * Bilinear sampling with boundary clamping
 **********************************************************/
inline float bilinear(const std::vector<float>& img,
                      int w, int h,
                      float x, float y)
{
    x = std::clamp(x, 0.0f, w - 1.0001f);
    y = std::clamp(y, 0.0f, h - 1.0001f);

    int x0 = (int) std::floor(x);
    int y0 = (int) std::floor(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float dx = x - x0;
    float dy = y - y0;

    float v00 = img[y0*w + x0];
    float v01 = img[y1*w + x0];
    float v10 = img[y0*w + x1];
    float v11 = img[y1*w + x1];

    float v0 = v00 * (1 - dy) + v01 * dy;
    float v1 = v10 * (1 - dy) + v11 * dy;

    return v0 * (1 - dx) + v1 * dx;
}


/**********************************************************
 * Slight Gaussian blur for pyramid before downsampling
 **********************************************************/
std::vector<float> gaussian5x5(const std::vector<float>& src,
                               int w, int h)
{
    // 5x5 Gaussian kernel (unnormalized)
    static const float k[5][5] =
    {
        {1,  4,  6,  4, 1},
        {4, 16, 24, 16, 4},
        {6, 24, 36, 24, 6},
        {4, 16, 24, 16, 4},
        {1,  4,  6,  4, 1}
    };
    static const float norm = 256.0f;

    std::vector<float> dst(w*h);

    for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
    {
        float sum = 0.0f;

        for (int ky = -2; ky <= 2; ky++)
        for (int kx = -2; kx <= 2; kx++)
        {
            int xx = std::clamp(x + kx, 0, w-1);
            int yy = std::clamp(y + ky, 0, h-1);
            sum += src[yy*w + xx] * k[ky+2][kx+2];
        }

        dst[y*w + x] = sum / norm;
    }

    return dst;
}


/**********************************************************
 * Downsample 2x with pre-blur
 **********************************************************/
std::vector<float> downsample2(const std::vector<float>& src,
                               int w, int h,
                               int& outW, int& outH)
{
    auto tmp = gaussian5x5(src, w, h);

    outW = w / 2;
    outH = h / 2;

    std::vector<float> dst(outW * outH);

    for (int y = 0; y < outH; y++)
    for (int x = 0; x < outW; x++)
        dst[y*outW + x] = tmp[(y*2)*w + (x*2)];

    return dst;
}


/**********************************************************
 * Flow field
 **********************************************************/
struct FlowField {
    int w, h;
    std::vector<float> u;
    std::vector<float> v;
};


/**********************************************************
 * Horn–Schunck on one resolution level
 **********************************************************/
void horn_schunck_level(
        const std::vector<float>& A,
        const std::vector<float>& B,
        int w, int h,
        std::vector<float>& u,
        std::vector<float>& v,
        float alpha = 20.0f,
        int iterations = 100)
{
    int N = w*h;

    std::vector<float> Ix(N), Iy(N), It(N);

    for (int y = 1; y < h-1; y++)
    for (int x = 1; x < w-1; x++)
    {
        int i = y*w + x;

        // Classic HS gradients (based only on A)
        Ix[i] = 0.5f * (A[i+1] - A[i-1]);
        Iy[i] = 0.5f * (A[i+w] - A[i-w]);
        It[i] = B[i] - A[i];
    }

    std::vector<float> u_new(N), v_new(N);

    for (int it = 0; it < iterations; it++)
    {
        for (int y = 1; y < h-1; y++)
        for (int x = 1; x < w-1; x++)
        {
            int i = y*w + x;

            float u_avg = (u[i-1] + u[i+1] + u[i-w] + u[i+w]) * 0.25f;
            float v_avg = (v[i-1] + v[i+1] + v[i-w] + v[i+w]) * 0.25f;

            float P = Ix[i]*u_avg + Iy[i]*v_avg + It[i];
            float D = alpha*alpha + Ix[i]*Ix[i] + Iy[i]*Iy[i];

            u_new[i] = u_avg - Ix[i] * P / D;
            v_new[i] = v_avg - Iy[i] * P / D;
        }

        u.swap(u_new);
        v.swap(v_new);
    }
}


/**********************************************************
 * Pyramid builder
 **********************************************************/
struct Pyramid {
    std::vector<std::vector<float>> levels;
    std::vector<int> W, H;
};

Pyramid build_pyramid(const std::vector<float>& base, int w, int h, int levels)
{
    Pyramid P;
    P.levels.push_back(base);
    P.W.push_back(w);
    P.H.push_back(h);

    for (int i = 1; i < levels; i++)
    {
        int nw, nh;
        auto ds = downsample2(P.levels.back(), P.W.back(), P.H.back(), nw, nh);
        P.levels.push_back(std::move(ds));
        P.W.push_back(nw);
        P.H.push_back(nh);
    }

    return P;
}


/**********************************************************
 * Upscale flow by factor of 2
 **********************************************************/
void upscale_flow(FlowField& F, int newW, int newH)
{
    std::vector<float> u2(newW*newH), v2(newW*newH);

    for (int y = 0; y < newH; y++)
    for (int x = 0; x < newW; x++)
    {
        float uf = bilinear(F.u, F.w, F.h, x/2.0f, y/2.0f) * 2.0f;
        float vf = bilinear(F.v, F.w, F.h, x/2.0f, y/2.0f) * 2.0f;

        u2[y*newW + x] = uf;
        v2[y*newW + x] = vf;
    }

    F.w = newW;
    F.h = newH;
    F.u.swap(u2);
    F.v.swap(v2);
}


/**********************************************************
 * Warp image with flow * t
 **********************************************************/
std::vector<float> warp_with_flow(
        const std::vector<float>& A,
        const FlowField& flow,
        float t)
{
    int w = flow.w, h = flow.h;
    std::vector<float> out(w*h);

    for (int i = 0; i < w*h; i++)
    {
        int x = i % w;
        int y = i / w;
        float nx = x + flow.u[i] * t;
        float ny = y + flow.v[i] * t;
        out[i] = bilinear(A, w, h, nx, ny);
    }
    return out;
}


/**********************************************************
 * Pyramid optical flow (full coarse-to-fine HS)
 **********************************************************/
FlowField pyramid_optical_flow(
        const std::vector<float>& A,
        const std::vector<float>& B,
        int w, int h,
        int levels = 4)
{
    Pyramid PA = build_pyramid(A, w, h, levels);
    Pyramid PB = build_pyramid(B, w, h, levels);

    int L = levels - 1;

    FlowField flow;
    flow.w = PA.W[L];
    flow.h = PA.H[L];
    flow.u.assign(flow.w * flow.h, 0.0f);
    flow.v.assign(flow.w * flow.h, 0.0f);

    for (int lvl = L; lvl >= 0; lvl--)
    {
        if (lvl != L)
            upscale_flow(flow, PA.W[lvl], PA.H[lvl]);

        // *** CORRECT: warp A using current flow ***
        auto Awarp = warp_with_flow(PA.levels[lvl], flow, 1.0f);

        horn_schunck_level(Awarp, PB.levels[lvl],
                           PA.W[lvl], PA.H[lvl],
                           flow.u, flow.v,
                           20.0f,
                           120);
    }

    return flow;
}


/**********************************************************
 * High-level interpolation function
 **********************************************************/
std::vector<float> transferInterpolation(
        const std::vector<float>& A,
        const std::vector<float>& B,
        int w, int h,
        float t)
{
    FlowField flow = pyramid_optical_flow(A, B, w, h, 4);

    return warp_with_flow(A, flow, t);
}


#endif


#include <vector>
#include <cmath>
#include <algorithm>

struct FlowField {
    int w, h;
    std::vector<float> u;
    std::vector<float> v;
};

/************** Bilinear interpolation with clamping **************/
inline float bilinear(const std::vector<float>& img, int w, int h, float x, float y)
{
    x = std::clamp(x, 0.f, float(w - 1));
    y = std::clamp(y, 0.f, float(h - 1));

    int x0 = int(x);
    int y0 = int(y);
    int x1 = std::min(x0 + 1, w - 1);
    int y1 = std::min(y0 + 1, h - 1);

    float dx = x - x0;
    float dy = y - y0;

    float v00 = img[y0*w + x0];
    float v01 = img[y1*w + x0];
    float v10 = img[y0*w + x1];
    float v11 = img[y1*w + x1];

    float v0 = v00 * (1 - dy) + v01 * dy;
    float v1 = v10 * (1 - dy) + v11 * dy;

    return v0 * (1 - dx) + v1 * dx;
}

/************** Downsample by 2 (simple box) **************/
std::vector<float> downsample2(const std::vector<float>& src, int w, int h, int& outW, int& outH)
{
    outW = w / 2;
    outH = h / 2;
    std::vector<float> dst(outW * outH);
    for (int y = 0; y < outH; y++)
        for (int x = 0; x < outW; x++)
            dst[y*outW + x] = src[(y*2)*w + (x*2)];
    return dst;
}

/************** Horn–Schunck optical flow at one resolution **************/
void horn_schunck_level(const std::vector<float>& A,
                        const std::vector<float>& B,
                        int w, int h,
                        std::vector<float>& u,
                        std::vector<float>& v,
                        float alpha=15.f,
                        int iterations=100)
{
    int N = w*h;
    std::vector<float> Ix(N), Iy(N), It(N);

    // Gradients (central differences)
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
            int i=y*w+x;
            Ix[i] = 0.f; Iy[i]=0.f;
            if(x>0 && x<w-1) Ix[i]=0.5f*(A[i+1]-A[i-1]+B[i+1]-B[i-1]);
            if(y>0 && y<h-1) Iy[i]=0.5f*(A[i+w]-A[i-w]+B[i+w]-B[i-w]);
            It[i] = B[i]-A[i];
        }
    }

    std::vector<float> u_new=u, v_new=v;
    float alpha2 = alpha*alpha;

    for(int it=0;it<iterations;it++){
        for(int y=0;y<h;y++){
            for(int x=0;x<w;x++){
                int i=y*w+x;
                float u_avg=0.f, v_avg=0.f; int count=0;
                if(x>0){u_avg+=u[i-1]; v_avg+=v[i-1]; count++;}
                if(x<w-1){u_avg+=u[i+1]; v_avg+=v[i+1]; count++;}
                if(y>0){u_avg+=u[i-w]; v_avg+=v[i-w]; count++;}
                if(y<h-1){u_avg+=u[i+w]; v_avg+=v[i+w]; count++;}
                if(count>0){ u_avg/=count; v_avg/=count; }
                float P = Ix[i]*u_avg + Iy[i]*v_avg + It[i];
                float D = alpha2 + Ix[i]*Ix[i] + Iy[i]*Iy[i];
                u_new[i] = u_avg - Ix[i]*P/D;
                v_new[i] = v_avg - Iy[i]*P/D;
            }
        }
        u.swap(u_new);
        v.swap(v_new);
    }
}

/************** Build Gaussian pyramid (no blur for simplicity) **************/
struct Pyramid{
    std::vector<std::vector<float>> levels;
    std::vector<int> W,H;
};

Pyramid build_pyramid(const std::vector<float>& base,int w,int h,int levels){
    Pyramid P;
    P.levels.push_back(base);
    P.W.push_back(w);
    P.H.push_back(h);
    for(int i=1;i<levels;i++){
        int nw,nh;
        auto ds = downsample2(P.levels.back(),P.W.back(),P.H.back(),nw,nh);
        P.levels.push_back(std::move(ds));
        P.W.push_back(nw);
        P.H.push_back(nh);
    }
    return P;
}

/************** Upscale flow by 2 **************/
void upscale_flow(FlowField &F,int newW,int newH){
    std::vector<float> u2(newW*newH), v2(newW*newH);
    for(int y=0;y<newH;y++){
        for(int x=0;x<newW;x++){
            float uf = bilinear(F.u,F.w,F.h,x/2.f,y/2.f)*2.f;
            float vf = bilinear(F.v,F.w,F.h,x/2.f,y/2.f)*2.f;
            u2[y*newW+x]=uf;
            v2[y*newW+x]=vf;
        }
    }
    F.w=newW; F.h=newH;
    F.u.swap(u2); F.v.swap(v2);
}

/************** Warp image with flow **************/
std::vector<float> warp_with_flow(const std::vector<float>& img,const FlowField &flow,float t,int iw,int ih){
    std::vector<float> out(flow.w*flow.h);
    for(int i=0;i<flow.w*flow.h;i++){
        int x=i%flow.w,y=i/flow.w;
        float nx=x+flow.u[i]*t;
        float ny=y+flow.v[i]*t;
        nx=std::clamp(nx,0.f,float(iw-1));
        ny=std::clamp(ny,0.f,float(ih-1));
        out[i]=bilinear(img,iw,ih,nx,ny);
    }
    return out;
}

/************** Pyramid optical flow **************/
FlowField pyramid_optical_flow(const std::vector<float>& A,const std::vector<float>& B,int w,int h,int levels=4){
    Pyramid PA=build_pyramid(A,w,h,levels);
    Pyramid PB=build_pyramid(B,w,h,levels);
    int L=levels-1;
    FlowField flow;
    flow.w=PA.W[L]; flow.h=PA.H[L];
    flow.u.assign(flow.w*flow.h,0.f);
    flow.v.assign(flow.w*flow.h,0.f);

    for(int lvl=L;lvl>=0;lvl--){
        if(lvl!=L) upscale_flow(flow,PA.W[lvl],PA.H[lvl]);
        auto Awarp = warp_with_flow(PA.levels[lvl],flow,1.f,PA.W[lvl],PA.H[lvl]);
        horn_schunck_level(Awarp,PB.levels[lvl],PA.W[lvl],PA.H[lvl],flow.u,flow.v);
    }
    return flow;
}

/************** Bidirectional interpolation **************/
std::vector<float> transferInterpolation(const std::vector<float>& A,const std::vector<float>& B,int w,int h,float t){
    FlowField flow_f = pyramid_optical_flow(A,B,w,h);
    FlowField flow_b = pyramid_optical_flow(B,A,w,h);

    std::vector<float> result(w*h);
    for(int i=0;i<w*h;i++){
        int x=i%w, y=i/w;
        float nx_f=x+flow_f.u[i]*t;
        float ny_f=y+flow_f.v[i]*t;
        float val_f = bilinear(A,w,h,nx_f,ny_f);

        float nx_b=x-flow_b.u[i]*(1-t);
        float ny_b=y-flow_b.v[i]*(1-t);
        float val_b = bilinear(B,w,h,nx_b,ny_b);

        result[i] = val_f*(1-t)+val_b*t;
    }
    return result;
}
