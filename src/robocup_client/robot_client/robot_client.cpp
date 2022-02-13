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

#include "robocup_client/robot_client/robot_client.hpp"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include <memory>
#include <string>
#include <vector>
#include <arpa/inet.h>

namespace robocup_client
{

namespace robot_client
{

const int max_answer_size = 1920 * 1080 * 3 + 1000;

RobotClient::RobotClient(const std::string & host, const int & port, std::shared_ptr<robocup_client::communication::TcpSocket> tcp_socket)
: robocup_client::communication::Client(host, port, tcp_socket)
{
}

bool RobotClient::connect()
{
  robocup_client::communication::Client::connect();

  std::string response = receive_string(8);

  return response.compare("Welcome") == 1;
}

void RobotClient::receive_data(char * buffer, int bytes)
{
  int received = 0;
  while (received < bytes) {
    int n = receive_raw(buffer + received, bytes - received);
    if (n == -1) {
      disconnect();
    }
    received += n;
  }
}

std::shared_ptr<SensorMeasurements> RobotClient::receive()
{
  uint32_t content_size_network = robocup_client::communication::Client::receive<uint32_t>().value_or(0);
  const int answer_size = ntohl(content_size_network);

  if (answer_size > max_answer_size || answer_size == 0) {
    disconnect();
  }

  SensorMeasurements sensor_measurements;
  std::vector<char> buffer(answer_size);
  receive_data(buffer.data(), answer_size);
  sensor_measurements.ParseFromArray(buffer.data(), answer_size);

  return std::make_shared<SensorMeasurements>(sensor_measurements);
}

int RobotClient::send(const ActuatorRequests & data)
{
  uint32_t size = htonl(data.ByteSizeLong());

  int sent = Client::send<uint32_t>(size);

  if (sent == 0) {
    disconnect();
  }

  google::protobuf::io::ZeroCopyOutputStream * zeroCopyStream =
    new google::protobuf::io::FileOutputStream(get_tcp_socket()->get_sockfd());

  data.SerializeToZeroCopyStream(zeroCopyStream);

  delete zeroCopyStream;

  return sent;
}

}  // namespace robot_client

}  // namespace robocup_client
