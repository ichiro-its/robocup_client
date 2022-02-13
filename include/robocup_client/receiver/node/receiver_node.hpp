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

#ifndef ROBOCUP_CLIENT__RECEIVER__NODE__RECEIVER_NODE_HPP_
#define ROBOCUP_CLIENT__RECEIVER__NODE__RECEIVER_NODE_HPP_

#include "robocup_client/communication/communication.hpp"
#include "robocup_client/robot_client/robot_client.hpp"
#include "tachimawari_interfaces/msg/set_joints.hpp"
#include "tachimawari_interfaces/msg/joint.hpp"
#include "robocup_client/receiver/node/receiver.hpp"

#include <string>
#include <memory>

#include "./messages.pb.h"

namespace robocup_client
{

namespace receiver
{

class ReceiverNode
{
public:
  ReceiverNode(
    rclcpp::Node::SharedPtr node, robocup_client::robot_client::RobotClient robot_client);
  
  private:
    std::string get_node_prefix() const;

    rclcpp::Subscription<tachimawari_interfaces::msg::SetJoints>::SharedPtr set_joints_subscriber;

    rclcpp::Service<tachimawari_interfaces::srv::GetJoints>::SharedPtr get_joints_server;
};

} // namespace receiver

}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__RECEIVER__NODE__RECEIVER_NODE_HPP_
