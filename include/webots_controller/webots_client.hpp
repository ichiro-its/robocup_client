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

#ifndef WEBOTS_CONTROLLER__WEBOTS_CLIENT_HPP_
#define WEBOTS_CONTROLLER__WEBOTS_CLIENT_HPP_

#include <memory>
#include <string>
#include <arpa/inet.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>


#include "messages.pb.h"
#include <musen/musen.hpp>

namespace webots_controller
{

class WebotsClient
{
public:
  WebotsClient(const std::string &host, int port) :
    host(host),
    port(port),
    sockfd(-1) {
  }

  void disconnect() {
    if (sockfd == -1) {
      fprintf(stderr, "RobotClient is already disconnected\n");
      return;
    }
    close(sockfd);
    sockfd = -1;
  }

  bool connectClient() {
    int return_code;
    struct hostent *server = gethostbyname(host.c_str());
    struct sockaddr_in address;
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (server)
      memcpy((char *)&address.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    else {
      fprintf(stderr, "Cannot resolve server name: %s\n", host.c_str());
      return false;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
      fprintf(stderr, "Cannot create socket\n");
      return false;
    }
    int attempt = 1;
    bool connected = false;
    while (attempt <= 20000) {
      return_code = connect(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr));
      if (return_code == 0) {
        connected = true;
        break;
      }
      fprintf(stderr, "Failed to connect to %s:%d (attempt %d / %d)\n", host.c_str(), port, attempt, 20000);
      attempt++;
      sleep(1);
    }
    if (!connected) {
      fprintf(stderr, "Failed to connect after %d attempts. Giving up on connection\n", attempt);
      disconnect();
      return false;
    }
    char answer[8];
    receiveData(answer, 8);
    printf("Welcome message: %s\n", answer);
    if (strncmp(answer, "Welcome", 8) != 0) {
      if (strncmp(answer, "Refused", 8) == 0)
        fprintf(stderr, "Connection to %s:%d refused: your IP address is not allowed in the game.json configuration file.\n",
                host.c_str(), port);
      else
        fprintf(stderr, "Received unknown answer from server: %s\n", answer);
      disconnect();
      return false;
    }
    printf("Connected to %s:%d\n", host.c_str(), port);
    return true;
  }

  void receiveData(char *buffer, int bytes) {
    if (sockfd == -1)
      throw std::logic_error("RobotClient is not connected");
    int received = 0;
    while (received < bytes) {
      int n = recv(sockfd, buffer + received, bytes - received, 0);
      if (n == -1) {
        std::string error_msg = "Failed to send message of size: " + std::to_string(bytes) + " errno: " + std::to_string(errno);
        if (errno == ECONNRESET)
          error_msg = "Simulator interrupted the connection";
        disconnect();
        throw std::runtime_error(error_msg);
      }
      received += n;
    }
  }

  SensorMeasurements receive() {
    uint32_t content_size_network;
    receiveData((char *)&content_size_network, sizeof(uint32_t));
    const int answer_size = ntohl(content_size_network);
    // if (answer_size > max_answer_size || answer_size == 0) {
    //   disconnectClient();
    //   throw std::logic_error("Unexpected size for the answer: " + std::to_string(answer_size) + " (probably out of sync)");
    // }
    SensorMeasurements sensor_measurements;
    char *buffer = (char *)malloc(answer_size);
    receiveData(buffer, answer_size);
    sensor_measurements.ParseFromArray(buffer, answer_size);
    free(buffer);

    std::string printout;
    google::protobuf::TextFormat::PrintToString(sensor_measurements, &printout);
    std::cout << printout << std::endl;
    
    return sensor_measurements;
  }

  void sendRequest(const ActuatorRequests &actuator_request) {
    if (sockfd == -1)
      throw std::logic_error("RobotClient is not connected");
    const uint32_t size = htonl(actuator_request.ByteSizeLong());
  
    if (send(sockfd, (char *)(&size), sizeof(uint32_t), 0) == -1) {
      std::string error_msg = "Failed to send message of size: " + std::to_string(size) + " errno: " + std::to_string(errno);
      if (errno == ECONNRESET)
        error_msg = "Simulator interrupted the connection";
      disconnect();
      throw std::runtime_error(error_msg);
    }
    google::protobuf::io::ZeroCopyOutputStream *zeroCopyStream = new google::protobuf::io::FileOutputStream(sockfd);
    actuator_request.SerializeToZeroCopyStream(zeroCopyStream);
    delete zeroCopyStream;
    // char *output = (char *)malloc(sizeof(int) + size);
    // uint32_t *content_size = (uint32_t *)output;
    // *content_size = size;
    // uint32_t total_size = sizeof(uint32_t) + *content_size;
    // actuator_request.SerializeToArray(&output[sizeof(uint32_t)], *content_size);
    // if (send(sockfd, output, total_size, 0) == -1) {
    //   std::string error_msg =
    //     "Failed to send message of size: " + std::to_string(total_size) + " errno: " + std::to_string(errno);
    //   free(output);
    //   disconnect();
    //   throw std::runtime_error(error_msg);
    // }
    // free(output);
  }

  int port;
  int sockfd;
  std::string host;
};

}  // webots_controller

#endif  // WEBOTS_CONTROLLER__WEBOTS_CLIENT_HPP_
