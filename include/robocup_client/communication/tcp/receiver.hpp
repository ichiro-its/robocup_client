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

#ifndef ROBOCUP_CLIENT__COMMUNICATION__RECEIVER_HPP_
#define ROBOCUP_CLIENT__COMMUNICATION__RECEIVER_HPP_

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace robocup_client
{

namespace communication
{

class Receiver
{
public:
  virtual size_t receive_raw(char * data, const size_t & length);

  std::string receive_string(const size_t & length);
  std::vector<std::string> receive_strings(
    const size_t & length, const std::string & delimiter = ",");

  template<typename T>
  std::optional<T> receive();
};

template<typename T>
std::optional<T> Receiver::receive()
{
  T data;

  auto received = receive_raw(reinterpret_cast<char *>(&data), sizeof(T));

  if (received < sizeof(T)) {
    return std::nullopt;
  }

  return std::make_optional<T>(std::move(data));
}

} // namespace communication

}  // namespace robocup_client

#endif  // ROBOCUP_CLIENT__COMMUNICATION__RECEIVER_HPP_
