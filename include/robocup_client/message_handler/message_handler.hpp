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

#ifndef ROBOCUP_CLIENT__MESSAGE_HANDLER__MESSAGE_HANDLER_HPP_
#define ROBOCUP_CLIENT__MESSAGE_HANDLER__MESSAGE_HANDLER_HPP_

#include <memory>
#include <string>
#include "robocup_client/messages.pb.h"

namespace robocup_client
{

namespace message_handler
{

class MessageHandler
{
public:
  MessageHandler();

  void add_motor_position_in_degree(std::string name, double position);
  void add_motor_position_in_radian(std::string name, double position);
  void add_motor_velocity(std::string name, double velocity);
  void add_motor_force(std::string name, double force);
  void add_motor_torque(std::string name, double torque);
  void add_motor_pid(std::string name, Vector3 pid);
  void add_sensor_time_step(std::string name, uint32_t timeStep);
  void add_camera_quality(std::string name, double quality);
  void add_camera_exposure(std::string name, double exposure);
  void clear_actuator_request();

  std::shared_ptr<ActuatorRequests> get_actuator_request();

private:
  std::shared_ptr<ActuatorRequests> actuator_request;
};

}  // namespace message_handler

}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__MESSAGE_HANDLER__MESSAGE_HANDLER_HPP_
