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

#include <robocup_client/robocup_client.hpp>

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char * argv[])
{
  if (argc < 3) {
    std::cerr << "Please specify the host and the port!" << std::endl;
    return 0;
  }
  std::string host = argv[1];
  int port = std::stoi(argv[2]);

  robocup_client::RobotClient client(host, port);
  if (!client.connect()) {
    std::cerr << "Failed to connect to server on port " <<
      client.get_port() << "!" << std::endl;

    return 1;
  }

  robocup_client::MessageHandler message;
  message.add_motor_position("Head", 1.2);
  message.add_motor_position("Neck", 0.8);
  message.add_sensor_time_step("Camera", 16);
  message.add_sensor_time_step("gyro", 8);
  message.add_sensor_time_step("accelerometer", 16);
  message.add_sensor_time_step("NeckS", 8);
  message.add_sensor_time_step("HeadS", 8);

  while (client.get_tcp_socket()->is_connected()) {
    try {
      client.send(*message.get_actuator_request());
      auto sensors = client.receive();

      // Get Gyro Data
      if (sensors.get()->gyros_size() > 0) {
        auto gyro = sensors.get()->gyros(0);
        std::cout << gyro.name() << " " << gyro.value().x() << " " << gyro.value().y() <<
          " " << gyro.value().z() << std::endl;
        std::cout << std::endl;
      }

      // Get Accelerometer Data
      if (sensors.get()->accelerometers_size() > 0) {
        auto accelerometer = sensors.get()->accelerometers(0);
        std::cout << accelerometer.name() << " " << accelerometer.value().x() << "  " <<
          accelerometer.value().y() <<
          " " << accelerometer.value().z() << std::endl;
        std::cout << std::endl;
      }

      // Get Position Sensor Data
      for (int i = 0; i < sensors.get()->position_sensors_size(); i++) {
        auto position_sensor = sensors.get()->position_sensors(i);
        std::cout << position_sensor.name() << " " << position_sensor.value() << std::endl;
      }
      std::cout << std::endl;

      // Get Camera Data
      if (sensors.get()->cameras_size() > 0) {
        auto camera = sensors.get()->cameras(0);
        std::cout << camera.name() << " " << camera.width() <<
          " " << camera.height() << " " << camera.quality() <<
          " " << sizeof(camera.image()) << std::endl;
      }
      std::cout << std::endl;
    } catch (const std::runtime_error & exc) {
      std::cerr << "Runtime error: " << exc.what() << std::endl;
    }
  }

  return 0;
}
