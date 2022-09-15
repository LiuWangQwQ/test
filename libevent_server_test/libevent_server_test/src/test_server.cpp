//
// Created by robot on 4/13/22.
//
#include "test_server.h"
void TestServer::ReadEvent(Conn *conn)
{
  conn->MoveBufferData();
}

void TestServer::WriteEvent(Conn *conn)
{

}

void TestServer::ConnectionEvent(Conn *conn)
{
  TestServer *me = (TestServer*)conn->GetThread()->tcpConnect;
  printf("new connection: %d\n", conn->GetFd());
  me->vec.push_back(conn);
}

void TestServer::CloseEvent(Conn *conn, short events)
{
  printf("connection closed: %d\n", conn->GetFd());
}

void TestServer::QuitCb(int sig, short events, void *data)
{
  printf("Catch the SIGINT signal, quit in one second\n");
  TestServer *me = (TestServer*)data;
  timeval tv = {1, 0};
  me->StopRun(&tv);
}

void TestServer::TimeOutCb(int id, short events, void *data)
{
  TestServer *me = (TestServer*)data;
  char temp[33] = "hello, world\n";
  for(int i=0; i<me->vec.size(); i++)
    me->vec[i]->AddToWriteBuffer(temp, strlen(temp));
}
