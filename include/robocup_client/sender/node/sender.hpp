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

#ifndef ROBOCUP_CLIENT__SENDER__NODE__SENDER_HPP_
#define ROBOCUP_CLIENT__SENDER__NODE__SENDER_HPP_

#include "robocup_client/communication/communication.hpp"
#include "robocup_client/robot_client/robot_client.hpp"
#include "shisen_interfaces/msg/image.hpp"
#include "tachimawari_interfaces/srv/get_joints.hpp"
#include "tachimawari_interfaces/msg/joint.hpp"
#include "kansei_interfaces/msg/orientation.hpp"
#include "kansei_interfaces/msg/unit.hpp"

#include <string>
#include <memory>

#include "./messages.pb.h"
#include <rclcpp/rclcpp.hpp>

namespace robocup_client
{

namespace sender
{

class Sender : public robocup_client::robot_client::RobotClient
{
public:
  explicit Sender(
    rclcpp::Node::SharedPtr node, robocup_client::robot_client::RobotClient client, robocup_client::MessageHandler message);

private:
  std::shared_ptr<GyroMeasurement> get_gyro_data();
  std::shared_ptr<AccelerometerMeasurement> get_accelerometer_data();
  std::shared_ptr<CameraMeasurement> get_camera_data();

  robocup_client::robot_client::RobotClient robot_client;
};

} // namespace sender

}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__SENDER__NODE__SENDER_HPP_
