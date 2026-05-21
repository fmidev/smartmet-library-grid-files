/*! \file TransferInterpolation.h
 *  \brief Optical-flow-based transfer interpolation algorithms (bilinear sampling,
 *  Gaussian blur, and forward/backward flow warping). Currently disabled — all code
 *  is conditionally excluded from compilation. */

#include <vector>
#include <cmath>
#include <algorithm>

struct FlowField
{
    int w, h;
    std::vector<float> u;
    std::vector<float> v;
};

/************** Bilinear interpolation with clamping **************/
inline float bilinear(const std::vector<float> &img, int w, int h, float x, float y)
{
  x = std::clamp(x, 0.f, float(w - 1));
  y = std::clamp(y, 0.f, float(h - 1));

  int x0 = int(x);
  int y0 = int(y);
  int x1 = std::min(x0 + 1, w - 1);
  int y1 = std::min(y0 + 1, h - 1);

  float dx = x - x0;
  float dy = y - y0;

  float v00 = img[y0 * w + x0];
  float v01 = img[y1 * w + x0];
  float v10 = img[y0 * w + x1];
  float v11 = img[y1 * w + x1];

  float v0 = v00 * (1 - dy) + v01 * dy;
  float v1 = v10 * (1 - dy) + v11 * dy;

  return v0 * (1 - dx) + v1 * dx;
}

/************** Downsample by 2 (simple box) **************/
std::vector<float> downsample2(const std::vector<float> &src, int w, int h, int &outW, int &outH)
{
  outW = w / 2;
  outH = h / 2;
  std::vector<float> dst(outW * outH);
  for (int y = 0; y < outH; y++)
    for (int x = 0; x < outW; x++)
      dst[y * outW + x] = src[(y * 2) * w + (x * 2)];
  return dst;
}

/************** Horn–Schunck optical flow at one resolution **************/
void horn_schunck_level(const std::vector<float> &A, const std::vector<float> &B, int w, int h, std::vector<float> &u, std::vector<float> &v, float alpha = 15.f, int iterations =
    100)
{
  int N = w * h;
  std::vector<float> Ix(N), Iy(N), It(N);

  // Gradients (central differences)
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int i = y * w + x;
      Ix[i] = 0.f;
      Iy[i] = 0.f;
      if (x > 0 && x < w - 1)
        Ix[i] = 0.5f * (A[i + 1] - A[i - 1] + B[i + 1] - B[i - 1]);
      if (y > 0 && y < h - 1)
        Iy[i] = 0.5f * (A[i + w] - A[i - w] + B[i + w] - B[i - w]);
      It[i] = B[i] - A[i];
    }
  }

  std::vector<float> u_new = u, v_new = v;
  float alpha2 = alpha * alpha;

  for (int it = 0; it < iterations; it++) {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        int i = y * w + x;
        float u_avg = 0.f, v_avg = 0.f;
        int count = 0;
        if (x > 0) {
          u_avg += u[i - 1];
          v_avg += v[i - 1];
          count++;
        }
        if (x < w - 1) {
          u_avg += u[i + 1];
          v_avg += v[i + 1];
          count++;
        }
        if (y > 0) {
          u_avg += u[i - w];
          v_avg += v[i - w];
          count++;
        }
        if (y < h - 1) {
          u_avg += u[i + w];
          v_avg += v[i + w];
          count++;
        }
        if (count > 0) {
          u_avg /= count;
          v_avg /= count;
        }
        float P = Ix[i] * u_avg + Iy[i] * v_avg + It[i];
        float D = alpha2 + Ix[i] * Ix[i] + Iy[i] * Iy[i];
        u_new[i] = u_avg - Ix[i] * P / D;
        v_new[i] = v_avg - Iy[i] * P / D;
      }
    }
    u.swap(u_new);
    v.swap(v_new);
  }
}

/************** Build Gaussian pyramid (no blur for simplicity) **************/
struct Pyramid
{
    std::vector<std::vector<float>> levels;
    std::vector<int> W, H;
};

Pyramid build_pyramid(const std::vector<float> &base, int w, int h, int levels)
{
  Pyramid P;
  P.levels.push_back(base);
  P.W.push_back(w);
  P.H.push_back(h);
  for (int i = 1; i < levels; i++) {
    int nw, nh;
    auto ds = downsample2(P.levels.back(), P.W.back(), P.H.back(), nw, nh);
    P.levels.push_back(std::move(ds));
    P.W.push_back(nw);
    P.H.push_back(nh);
  }
  return P;
}

/************** Upscale flow by 2 **************/
void upscale_flow(FlowField &F, int newW, int newH)
{
  std::vector<float> u2(newW * newH), v2(newW * newH);
  for (int y = 0; y < newH; y++) {
    for (int x = 0; x < newW; x++) {
      float uf = bilinear(F.u, F.w, F.h, x / 2.f, y / 2.f) * 2.f;
      float vf = bilinear(F.v, F.w, F.h, x / 2.f, y / 2.f) * 2.f;
      u2[y * newW + x] = uf;
      v2[y * newW + x] = vf;
    }
  }
  F.w = newW;
  F.h = newH;
  F.u.swap(u2);
  F.v.swap(v2);
}

/************** Warp image with flow **************/
std::vector<float> warp_with_flow(const std::vector<float> &img, const FlowField &flow, float t, int iw, int ih)
{
  std::vector<float> out(flow.w * flow.h);
  for (int i = 0; i < flow.w * flow.h; i++) {
    int x = i % flow.w, y = i / flow.w;
    float nx = x + flow.u[i] * t;
    float ny = y + flow.v[i] * t;
    nx = std::clamp(nx, 0.f, float(iw - 1));
    ny = std::clamp(ny, 0.f, float(ih - 1));
    out[i] = bilinear(img, iw, ih, nx, ny);
  }
  return out;
}

/************** Pyramid optical flow **************/
FlowField pyramid_optical_flow(const std::vector<float> &A, const std::vector<float> &B, int w, int h, int levels = 4)
{
  Pyramid PA = build_pyramid(A, w, h, levels);
  Pyramid PB = build_pyramid(B, w, h, levels);
  int L = levels - 1;
  FlowField flow;
  flow.w = PA.W[L];
  flow.h = PA.H[L];
  flow.u.assign(flow.w * flow.h, 0.f);
  flow.v.assign(flow.w * flow.h, 0.f);

  for (int lvl = L; lvl >= 0; lvl--) {
    if (lvl != L)
      upscale_flow(flow, PA.W[lvl], PA.H[lvl]);
    auto Awarp = warp_with_flow(PA.levels[lvl], flow, 1.f, PA.W[lvl], PA.H[lvl]);
    horn_schunck_level(Awarp, PB.levels[lvl], PA.W[lvl], PA.H[lvl], flow.u, flow.v);
  }
  return flow;
}

/************** Bidirectional interpolation **************/
std::vector<float> transferInterpolation(const std::vector<float> &A, const std::vector<float> &B, int w, int h, float t)
{
  FlowField flow_f = pyramid_optical_flow(A, B, w, h);
  FlowField flow_b = pyramid_optical_flow(B, A, w, h);

  std::vector<float> result(w * h);
  for (int i = 0; i < w * h; i++) {
    int x = i % w, y = i / w;
    float nx_f = x + flow_f.u[i] * t;
    float ny_f = y + flow_f.v[i] * t;
    float val_f = bilinear(A, w, h, nx_f, ny_f);

    float nx_b = x - flow_b.u[i] * (1 - t);
    float ny_b = y - flow_b.v[i] * (1 - t);
    float val_b = bilinear(B, w, h, nx_b, ny_b);

    result[i] = val_f * (1 - t) + val_b * t;
  }
  return result;
}
