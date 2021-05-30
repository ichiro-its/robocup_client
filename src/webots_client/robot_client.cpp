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

#include <webots_client/robot_client.hpp>

#include <cstring>
#include <string>
#include <memory>

#include <musen/musen.hpp>

namespace webots_client
{

RobotClient::RobotClient(
  const std::string & host, const int & port, std::shared_ptr<musen::TcpSocket> tcp_socket)
: musen::BaseClient(host, port, tcp_socket)
{
}

bool RobotClient::connect()
{
  musen::BaseClient::connect();

  char response[8];
  musen::BaseClient::receive(response, 8);

  if (strncmp(response, "Welcome", 8) != 0) {
    return false;
  }

  return true;
}

std::shared_ptr<SensorMeasurements> RobotClient::receive()
{
  auto data = std::make_shared<SensorMeasurements>();

  int received = musen::BaseClient::receive(data.get(), sizeof(SensorMeasurements));

  if (received < (signed)sizeof(SensorMeasurements)) {
    return nullptr;
  }

  return data;
}

int RobotClient::send(const ActuatorRequests & data)
{
  return musen::BaseClient::send((const char *)&data, sizeof(data));
}

} // namespace webots_client
