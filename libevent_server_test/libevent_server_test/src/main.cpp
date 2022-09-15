
#include <ros/ros.h>
#include "test_server.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "libevent_server_test_node");
  std::setlocale(LC_ALL, "zh_CN.UTF-8");  //打印中文log
  ros::NodeHandle nh;

  ROS_INFO("pid: %d", getpid());
  TestServer server(3);
  server.AddSignalEvent(SIGINT, TestServer::QuitCb);
  timeval tv = {10, 0};
  server.AddTimerEvent(TestServer::TimeOutCb, tv, false);
  server.SetPort(8080);
  server.StartRun();


  ros::MultiThreadedSpinner spinner(2);
  spinner.spin();

  ROS_INFO("libevent_server_test_node 节点已退出");
  return 0;
}
