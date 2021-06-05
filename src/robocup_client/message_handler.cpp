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

#include <keisan/keisan.hpp>
#include <robocup_client/robocup_client.hpp>
#include <memory>
#include <string>

namespace robocup_client
{


MessageHandler::MessageHandler()
: actuator_request(std::make_shared<ActuatorRequests>())
{
}

void MessageHandler::add_motor_position_in_degree(std::string name, double position)
{
  auto motor_position = actuator_request->add_motor_positions();
  motor_position->set_name(name);
  motor_position->set_position(keisan::deg_to_rad(position));
}

void MessageHandler::add_motor_position_in_radian(std::string name, double position)
{
  auto motor_position = actuator_request->add_motor_positions();
  motor_position->set_name(name);
  motor_position->set_position(position);
}

void MessageHandler::add_motor_velocity(std::string name, double velocity)
{
  auto motor_velocity = actuator_request->add_motor_velocities();
  motor_velocity->set_name(name);
  motor_velocity->set_velocity(velocity);
}

void MessageHandler::add_motor_force(std::string name, double force)
{
  auto motor_force = actuator_request->add_motor_forces();
  motor_force->set_name(name);
  motor_force->set_force(force);
}

void MessageHandler::add_motor_torque(std::string name, double torque)
{
  auto motor_torque = actuator_request->add_motor_torques();
  motor_torque->set_name(name);
  motor_torque->set_torque(torque);
}

void MessageHandler::add_motor_pid(std::string name, Vector3 pid)
{
  auto motor_pid = actuator_request->add_motor_pids();
  motor_pid->set_name(name);
  motor_pid->set_allocated_pid(&pid);
}

void MessageHandler::add_sensor_time_step(std::string name, uint32_t timeStep)
{
  auto sensor = actuator_request->add_sensor_time_steps();
  sensor->set_name(name);
  sensor->set_timestep(timeStep);
}

void MessageHandler::add_camera_quality(std::string name, double quality)
{
  auto camera = actuator_request->add_camera_qualities();
  camera->set_name(name);
  camera->set_quality(quality);
}

void MessageHandler::add_camera_exposure(std::string name, double exposure)
{
  auto camera = actuator_request->add_camera_exposures();
  camera->set_name(name);
  camera->set_exposure(exposure);
}

void MessageHandler::clear_actuator_request()
{
  actuator_request.reset(new ActuatorRequests);
}

std::shared_ptr<ActuatorRequests> MessageHandler::get_actuator_request()
{
  return actuator_request;
}

}  // namespace robocup_client
