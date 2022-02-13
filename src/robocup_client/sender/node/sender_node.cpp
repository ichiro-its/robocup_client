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

#include "robocup_client/sender/sender.hpp"
#include "./messages.pb.h"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include <memory>
#include <string>
#include <vector>
#include <arpa/inet.h>

namespace robocup_client
{

namespace sender
{

SenderNode::SenderNode(rclcpp::Node::SharedPtr node, robocup_client::sender::Sender sender)
: sender(sender)
{
  image_publisher = node->create_publisher<shisen_interfaces::msg::Image>(
    get_node_prefix() + "/image", 10););

  unit_publisher = node->create_publisher<kansei_interfaces::msg::Unit>(
    get_node_prefix() + "/unit", 10);
}

std::string SenderNode::get_node_prefix() const 
{
  return "sender";
}

void publish_image()
{
  auto image_msg = shisen_interfaces::msg::Image();
  auto image_webots = sender->get_camera_data();

  // convert image_webots into image_msg

  image_publisher->publish(image_msg);
}

void publish_unit()
{
  auto unit_msg = kansei_interfaces::msg::Unit();

  auto gyro = sender->get_gyro_data();
  auto accelero = sender->get_accelerometer_data();

  unit_msg.gyro = {static_cast<float>(gyro.value().x()), static_cast<float>(gyro.value().y()),
    static_cast<float>(gyro.value().z())};
  unit_msg.accelero = {static_cast<float>(accelerometer.value().x()), static_cast<float>(accelerometer.value().y()),
    static_cast<float>(accelerometer.value().z())};

  unit_publisher->publish(unit_msg);
}

} // namespace sender

}  // namespace robocup_client
