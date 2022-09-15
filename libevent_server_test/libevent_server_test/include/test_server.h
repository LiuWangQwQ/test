//
// Created by robot on 4/13/22.
//

#ifndef TEST_SERVER_H_
#define TEST_SERVER_H_

/*
这是一个测试用的服务器，只有两个功能：
1：对于每个已连接客户端，每10秒向其发送一句hello, world
2：若客户端向服务器发送数据，服务器收到后，再将数据回发给客户端
*/
//test.cpp
#include "tcp_event_server.h"
#include <set>
#include <vector>
using namespace std;

//测试示例
class TestServer : public TcpEventServer
{
private:
  vector<Conn*> vec;
protected:
  //重载各个处理业务的虚函数
  void ReadEvent(Conn *conn) override;
  void WriteEvent(Conn *conn) override;
  void ConnectionEvent(Conn *conn) override;
  void CloseEvent(Conn *conn, short events) override;
public:
  TestServer(int count) : TcpEventServer(count) { }
  ~TestServer() { }

  //退出事件，响应Ctrl+C
  static void QuitCb(int sig, short events, void *data);
  //定时器事件，每10秒向所有客户端发一句hello, world
  static void TimeOutCb(int id, int short events, void *data);
};



#endif // TEST_SERVER_H_
