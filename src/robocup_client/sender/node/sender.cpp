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

const int max_answer_size = 1920 * 1080 * 3 + 1000;

Sender::Sender(rclcpp::Node::SharedPtr node, robocup_client::robot_client::RobotClient client, robocup_client::MessageHandler message)
: robot_client(client), message(message)
{
  message.add_sensor_time_step("Camera", 16);
  message.add_sensor_time_step("gyro", 8);
  message.add_sensor_time_step("accelerometer", 8);

  robot_client.send(*message.get_actuator_request());
}

std::shared_ptr<GyroMeasurement> get_gyro_data()
{
  auto sensors = robot_client.receive();

  if (sensors.get()->gyros_size() > 0) {
    auto gyro = sensors.get()->gyros(0);
    return gyro;
  }
}

std::shared_ptr<AccelerometerMeasurement> get_accelerometer_data()
{
  auto sensors = robot_client.receive();

  if (sensors.get()->accelerometers_size() > 0) {
    auto accelerometer = sensors.get()->accelerometers(0);
    return accelerometer;
  }
}

std::shared_ptr<CameraMeasurement> get_camera_data()
{
  auto sensors = robot_client.receive();

  if (sensors.get()->cameras_size() > 0) {
    auto camera = sensors.get()->cameras(0);
    std::cout << camera.name() << " " << camera.width() << " " << camera.height() << " " << camera.quality() << " " << sizeof(camera.image()) << std::endl;

    return camera;
  }
}


} // namespace sender

}  // namespace robocup_client
