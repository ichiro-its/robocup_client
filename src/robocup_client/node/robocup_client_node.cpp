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

#include <rclcpp/rclcpp.hpp>

#include <chrono>
#include <memory>
#include <string>

#include "robocup_client/node/robocup_client_node.hpp"

using namespace std::chrono_literals;

namespace robocup_client
{

RobocupClientNode::RobocupClientNode(rclcpp::Node::SharedPtr node)
: node(node)
{
  node_timer = node->create_wall_timer(
    8ms,
    [this]() {
      // update gyro, accelero, time, and image
      robot_client->update_sensors();
    }
  );

  receiver_node = std::make_shared<robocup_client::receiver::ReceiverNode>(node, robot_client);
  sender_node = std::make_shared<robocup_client::sender::SenderNode>(node, robot_client);
}

void RobocupClientNode::set_robot_client(
  std::shared_ptr<robocup_client::robot_client::RobotClient> robot_client)
{
  this->robot_client = robot_client;
}

}  // namespace robocup_client
