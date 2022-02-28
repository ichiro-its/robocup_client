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

#ifndef ROBOCUP_CLIENT__ROBOT_CLIENT__ROBOT_CLIENT_HPP_
#define ROBOCUP_CLIENT__ROBOT_CLIENT__ROBOT_CLIENT_HPP_

#include <string>
#include <memory>
#include <vector>

#include "./messages.pb.h"
#include "robocup_client/communication/communication.hpp"
#include "robocup_client/message_handler/message_handler.hpp"
#include "tachimawari/joint/model/joint.hpp"
#include "tachimawari/joint/model/joint_id.hpp"

namespace robocup_client
{

namespace robot_client
{

class RobotClient : public robocup_client::communication::Client
{
public:
  explicit RobotClient(
    const std::string & host, const int & port,
    std::shared_ptr<robocup_client::communication::TcpSocket>
    tcp_socket = std::make_shared<robocup_client::communication::TcpSocket>(),
    int time_step = 8, int camera_time_step = 16);

  bool connect();
  void receive_data(char * buffer, int bytes);
  int send(const ActuatorRequests & data);
  std::shared_ptr<SensorMeasurements> receive();

  void update_sensors();
  void set_positions(std::vector<tachimawari::joint::Joint> joints);

  std::vector<PositionSensorMeasurement> get_positions();
  AccelerometerMeasurement get_accelero();
  CameraMeasurement get_camera();
  GyroMeasurement get_gyro();

private:
  AccelerometerMeasurement current_accelero;
  CameraMeasurement current_camera;
  GyroMeasurement current_gyro;
  std::vector<PositionSensorMeasurement> current_positions;

  std::shared_ptr<robocup_client::message_handler::MessageHandler> message;
};

}  // namespace robot_client

}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__ROBOT_CLIENT__ROBOT_CLIENT_HPP_
