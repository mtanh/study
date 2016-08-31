#ifndef DGS_SERVER_H_
#define DGS_SERVER_H_

class Builder
{
public:
  Builder();
  ~Builder();

private:
  int mGeneration;
};

class DGSServer
{
public:
  DGSServer();
  ~DGSServer();

  void StartServer();

private:
  Builder *mBuilder_;
  int mGeneration_;
};

#endif
