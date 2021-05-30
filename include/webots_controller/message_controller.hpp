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

#ifndef WEBOTS_CONTROLLER__MESSAGE_CONTROLLER_HPP_
#define WEBOTS_CONTROLLER__MESSAGE_CONTROLLER_HPP_

#include "./messages.pb.h"

namespace webots_controller
{

class MessageController {
public:
MessageController()
{
}

void addMotorPosition(MotorPosition* motorPosition, std::string name, double position)
{
  motorPosition->set_name(name);
  motorPosition->set_position(position);
}

void addMotorVelocities (MotorVelocity* motorVelocity, std::string name, double velocity)
{
  motorVelocity->set_name(name);
  motorVelocity->set_velocity(velocity);
}

void addMotorForces (MotorForce* motorForce, std::string name, double force)
{
  motorForce->set_name(name);
  motorForce->set_force(force);
}

void addMotorTorque (MotorTorque* motorTorque, std::string name, double torque)
{
  motorTorque->set_name(name);
  motorTorque->set_torque(torque);
}

void addMotorPID (MotorPID* motorPID, std::string name, Vector3 PID)
{
  motorPID->set_name(name);
  motorPID->set_allocated_pid(&PID);
}

void addSensorTimeStep (SensorTimeStep* sensor, std::string name, uint32_t timeStep)
{
  sensor->set_name(name);
  sensor->set_timestep(timeStep);
}

void addCameraQuality (CameraQuality* camera, std::string name, double quality)
{
  camera->set_name(name);
  camera->set_quality(quality);
}

void addCameraExposure (CameraExposure* camera, std::string name, double exposure)
{
  camera->set_name(name);
  camera->set_exposure(exposure);
}

  ActuatorRequests actuatorRequests;
};

}  // namespace webots_controller

#endif  // WEBOTS_CONTROLLER__MESSAGE_CONTROLLER_HPP_