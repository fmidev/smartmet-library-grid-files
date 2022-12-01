#include "DataFetcher_filesys.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>
#include "ShowFunction.h"

#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{

DataFetcher::DataFetcher()
{
  mDebugEnabled = false;
}




DataFetcher::~DataFetcher()
{
}





long long DataFetcher::getFileSize(uint serverType,uint protocol,const char *server,const char *filename)
{
  throw Fmi::Exception(BCP,"This method should be implemented in child classes!");
}




void DataFetcher::getFileHeaders(uint serverType,uint protocol,const char *server,const char *filename,std::map<std::string,std::string>& headers)
{
  throw Fmi::Exception(BCP,"This method should be implemented in child classes!");
}




int DataFetcher::getData(uint serverType,uint protocol,const char *server,const char *filename,std::size_t filePosition,int dataSize,char *dataPtr)
{
  throw Fmi::Exception(BCP,"This method should be implemented in child classes!");
}




void DataFetcher::getFileList(uint serverType,uint protocol,const char *server,const char *dir,std::vector<std::string> &filePatterns,std::vector<FileRec>& fileList)
{
  throw Fmi::Exception(BCP,"This method should be implemented in child classes!");
}



void DataFetcher::setDebugEnabled(bool enabled)
{
  mDebugEnabled = enabled;
}



void DataFetcher::setAccessFile(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    loadAccessFile(filename,mAccessMap);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void DataFetcher::loadAccessFile(const char *filename,AccessMap& mAccessMap)
{
  FUNCTION_TRACE
  try
  {
    mAccessMap.clear();

    if (filename == nullptr || filename[0] == '\0')
      return;

    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[1000];

    while (!feof(file))
    {
      if (fgets(st,1000,file) != nullptr  &&  st[0] != '#')
      {
        bool ind = false;
        char *field[100];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 3)
        {
          std::string server;
          AccessInfo rec;

          if (field[0][0] != '\0')
            server = field[0];

          if (field[1][0] != '\0')
            rec.authenticationMethod = toUInt32(field[1]);

          if (field[2][0] != '\0')
            rec.username = field[2];

          if (field[3][0] != '\0')
            rec.password = field[3];

          std::string key = toLowerString(server);
          //printf("ADD ACCESS [%s][%u][%s][%s]\n",server.c_str(),rec.authenticationMethod,rec.username.c_str(),rec.password.c_str());
          mAccessMap.insert(std::pair<std::string,AccessInfo>(key,rec));
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void DataFetcher::addAccessInfo(const char *server,uint authenticationMethod,const char *username,const char *password)
{
  FUNCTION_TRACE
  try
  {
    AccessInfo rec;
    rec.authenticationMethod = authenticationMethod;
    rec.username = username;
    rec.password = password;

    std::string key = toLowerString(server);
    mAccessMap.insert(std::pair<std::string,AccessInfo>(key,rec));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




DataFetcher::AccessInfo* DataFetcher::getAccessInfo(const char *server)
{
  FUNCTION_TRACE
  try
  {
    if (mAccessMap.size() == 0)
      return NULL;

    std::string key = toLowerString(server);
    auto rec = mAccessMap.find(key);
    if (rec != mAccessMap.end())
      return &rec->second;

    return NULL;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void DataFetcher::parseHeaders(char *data,int dataSize,std::map<std::string,std::string>& headers)
{
  FUNCTION_TRACE
  try
  {
    if (dataSize <= 0)
      return;

    char dat[dataSize];
    memcpy(dat,data,dataSize);

    int c = 0;
    char *p = dat;
    char *line[200];
    line[0] = dat;
    while (*p != '\0' && c < 200)
    {
      if (*p == '\r')
        *p = '\0';

      if (*p == '\n')
      {
        c++;
        line[c] = p + 1;
      }
      p++;
    }

    for (int t=0; t<c; t++)
    {
      //printf("[%s]\n",line[t]);
      char *p = strstr(line[t],":");
      if (p)
      {
        *p = '\0';
        p++;
        while (*p > '\0'  &&  *p <= ' ')
          p++;

        std::string key = toUpperString(line[t]);
        //printf("[%s][%s]\n",key.c_str(),p);
        auto it = headers.find(key);
        if (it != headers.end())
          headers.erase(it);

        headers.insert(std::pair<std::string,std::string>(key,std::string(p)));
      }
    }
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void DataFetcher::splitUrl(const char *urlStr,uint& protocol,std::string& server,std::string& filename)
{
  FUNCTION_TRACE
  try
  {
    if (!urlStr)
      return;

    char url[3000];
    strcpy(url,urlStr);
    char *s = url;

    protocol = 0;
    if (strncasecmp(url,"http://",7) == 0)
    {
      protocol = 1;
      s = url+7;
    }
    else
    if (strncasecmp(url,"https://",8) == 0)
    {
      protocol = 2;
      s = url+8;
    }

    char *path = strstr(s,"/");
    if (path)
    {
      *path = '\0';
      server = s;
      *path = '/';
      filename = path;
    }
    else
    {
      server = s;
      filename = "/";
    }
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}  // namespace SmartMet
