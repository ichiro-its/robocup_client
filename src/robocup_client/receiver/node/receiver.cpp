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

const int max_answer_size = 1920 * 1080 * 3 + 1000;

Receiver::Receiver(rclcpp::Node::SharedPtr node, robocup_client::robot_client::RobotClient client, robocup_client::MessageHandler message)
: robot_client(client), message(message)
{
  message.add_sensor_time_step("neck_yaw_s", 8);
  message.add_sensor_time_step("neck_pitch_s", 8);
  message.add_sensor_time_step("left_shoulder_pitch_s", 8);
  message.add_sensor_time_step("left_shoulder_roll_s", 8);
  message.add_sensor_time_step("left_elbow_s", 8);
  message.add_sensor_time_step("right_shoulder_pitch_s", 8);
  message.add_sensor_time_step("right_shoulder_roll_s", 8);
  message.add_sensor_time_step("right_elbow_s", 8);
  message.add_sensor_time_step("left_hip_yaw_s", 8);
  message.add_sensor_time_step("left_hip_roll_s", 8);
  message.add_sensor_time_step("left_hip_pitch_s", 8);
  message.add_sensor_time_step("left_knee_s", 8);
  message.add_sensor_time_step("left_ankle_roll_s", 8);
  message.add_sensor_time_step("left_ankle_pitch_s", 8);
  message.add_sensor_time_step("right_hip_yaw_s", 8);
  message.add_sensor_time_step("right_hip_roll_s", 8);
  message.add_sensor_time_step("right_hip_pitch_s", 8);
  message.add_sensor_time_step("right_knee_s", 8);
  message.add_sensor_time_step("right_ankle_roll_s", 8);
  message.add_sensor_time_step("right_ankle_pitch_s", 8);

  robot_client.send(*message.get_actuator_request());
}

std::shared_ptr<PositionSensorMeasurement> get_positions_data()
{
  auto sensors = robot_client->receive();

  for (int i = 0; i < sensors.get()->position_sensors_size(); i++) {
    auto position_sensor = sensors.get()->position_sensors(i);
  }
}

void set_positions_by_joints(std::vector<tachimawari_interfaces::msg::Joint> joints)
{
  message.clear_actuator_request();
    for (auto joint : joints) {
      std::string joint_name = joint.get_joint_name();
      float position = joint.get_goal_position();

      if (joint_name.find("shoulder_pitch") != std::string::npos) {
        joint_name += " [shoulder]";
      } else if (joint_name.find("hip_yaw") != std::string::npos) {
        joint_name += " [hip]", joint.get_goal_position();
      }

      message.add_motor_position_in_degree(joint_name, position);
    }
  robot_client.send(*message.get_actuator_request());
}

}  // namespace receiver

}  // namespace robocup_client
