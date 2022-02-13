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

#include "./messages.pb.h"
#include "robocup_client/robocup_client.hpp"

namespace robocup_client
{

namespace robot_client
{

class RobotClient : public robocup_client::communication::Client
{
public:
  explicit RobotClient(
    const std::string & host, const int & port, std::shared_ptr<robocup_client::communication::TcpSocket> tcp_socket = std::make_shared<robocup_client::communication::TcpSocket>());

  bool connect();
  void receive_data(char * buffer, int bytes);
  int send(const ActuatorRequests & data);
  std::shared_ptr<SensorMeasurements> receive();

  void update_sensors();
  void set_positions(std::vector<tachimawari_interfaces::msg::Joint> joints);

  std::shared_ptr<std::vector<PositionSensorMeasurement>> get_positions();
  std::shared_ptr<AccelerometerMeasurement> get_accelero();
  std::shared_ptr<CameraMeasurement> get_camera();
  std::shared_ptr<GyroMeasurement> get_gyro();

private:
  std::shared_ptr<AccelerometerMeasurement> current_accelero;
  std::shared_ptr<CameraMeasurement> current_camera;
  std::shared_ptr<GyroMeasurement> current_gyro;
  std::shared_ptr<std::vector<PositionSensorMeasurement>> current_positions;
  
  robocup_client::message_handler::MessageHandler message;
};

} // namespace robot_client

}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__ROBOT_CLIENT__ROBOT_CLIENT_HPP_
