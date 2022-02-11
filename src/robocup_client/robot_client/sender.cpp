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

#include "robocup_client/robot_client/sender.hpp"

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

Sender::Sender(
  const std::string & host, const int & port, std::shared_ptr<robocup_client::communication::TcpSocket> tcp_socket)
: robocup_client::communication::Client(host, port, tcp_socket)
{
}

bool Sender::connect()
{
  robocup_client::communication::Client::connect();

  std::string response = receive_string(8);

  return response.compare("Welcome") == 1;
}


int Sender::send(const ActuatorRequests & data)
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

} // namespace robot_client

}  // namespace robocup_client
