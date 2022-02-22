// Copyright (c) 2021 ICHIRO ITS
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef ROBOCUP_CLIENT__NODE__ROBOCUP_CLIENT_NODE_HPP_
#define ROBOCUP_CLIENT__NODE__ROBOCUP_CLIENT_NODE_HPP_

#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robocup_client/robocup_client.hpp"

namespace robocup_client
{

class RobocupClientNode
{
public:
  explicit RobocupClientNode(rclcpp::Node::SharedPtr node);

  void set_robot_client(std::shared_ptr<robocup_client::robot_client::RobotClient> robot_client);

private:
  rclcpp::Node::SharedPtr node;
  rclcpp::TimerBase::SharedPtr node_timer;

  std::shared_ptr<robocup_client::robot_client::RobotClient> robot_client;
  std::shared_ptr<robocup_client::sender::SenderNode> sender_node;
  std::shared_ptr<robocup_client::receiver::ReceiverNode> receiver_node;
};

}  //  namespace robocup_client

#endif  // ROBOCUP_CLIENT__NODE__ROBOCUP_CLIENT_NODE_HPP_
