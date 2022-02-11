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

#ifndef ROBOCUP_CLIENT__COMMUNICATION__TCP__CLIENT_HPP_
#define ROBOCUP_CLIENT__COMMUNICATION__TCP__CLIENT_HPP_

#include <memory>
#include <string>

#include "robocup_client/communication/_socket/tcp_socket.hpp"
#include "robocup_client/communication/tcp/receiver.hpp"
#include "robocup_client/communication/tcp/sender.hpp"

namespace robocup_client
{

namespace communication
{

class Client : public Sender, public Receiver
{
public:
  explicit Client(
    const std::string & host, const int & port,
    std::shared_ptr<TcpSocket> tcp_socket = std::make_shared<TcpSocket>());

  bool connect();
  bool disconnect();

  size_t send_raw(const char * data, const size_t & length) override;
  size_t receive_raw(char * data, const size_t & length) override;

  std::shared_ptr<TcpSocket> get_tcp_socket() const;

  bool is_connected() const;

  const std::string & get_host() const;
  const int & get_port() const;

protected:
  std::shared_ptr<TcpSocket> tcp_socket;

  std::string host;
  int port;
};

}  // namespace communication
 
}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__COMMUNICATION__TCP__CLIENT_HPP_
