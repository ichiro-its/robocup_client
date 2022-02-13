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

#include "robocup_client/receiver/receiver.hpp"
#include "robocup_client/robot_client/robot_client.hpp"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include <memory>
#include <string>
#include <vector>
#include <arpa/inet.h>

namespace robocup_client
{

namespace receiver
{

ReceiverNode::ReceiverNode(rclcpp::Node::SharedPtr node, robocup_client::receiver::Receiver receiver)
: receiver(receiver)
{
  set_joint_subscriber = node->create_subscription<tachimawari_interfaces::msg::SetJoints>(
    get_node_prefix() + "/set_joints", 10, 
    [this](const tachimawari_interfaces::msg::SetJoints::SharedPtr message) {
      std::vector<tachimawari_interfaces::msg::Joint> joints;

      for (const auto & joint : message->joints) {
        joints.push_back(Joint(joint.is, joint.position));
      }

      receiver->set_positions_by_joints(joints);  
    }
  );

  {
    using tachimawari_interfaces::srv::GetJoints;

    get_joints_server = node->create_service<tachimawari_interfaces::srv::GetJoints>(
      get_node_prefix() + "/get_joints",
      [this](std::shared_ptr<GetJoints::Request> request,
      std::shared_ptr<GetJoints::Respones> response) {
      }
    );
  }
}

std::string ReceiverNode::get_node_prefix() const
{
  return "receiver";
}

}  // namespace receiver

}  // namespace robocup_client
