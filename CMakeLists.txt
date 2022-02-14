cmake_minimum_required(VERSION 3.5)
project(robocup_client)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -fPIC)
endif()

find_package(ament_cmake REQUIRED)
find_package(kansei_interfaces REQUIRED)
find_package(keisan REQUIRED)
find_package(Protobuf REQUIRED)
find_package(rclcpp REQUIRED)
find_package(shisen_interfaces REQUIRED)
find_package(tachimawari_interfaces REQUIRED)
find_package(tachimawari REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER include/robocup_client/messages.proto)

add_library(${PROJECT_NAME} SHARED
  "examples/client.cpp"
  "src/${PROJECT_NAME}/communication/tcp/receiver.cpp"
  "src/${PROJECT_NAME}/communication/tcp/sender.cpp"
  "src/${PROJECT_NAME}/communication/tcp/client.cpp"
  "src/${PROJECT_NAME}/communication/socket/base_socket.cpp"
  "src/${PROJECT_NAME}/communication/socket/tcp_socket.cpp"
  "src/${PROJECT_NAME}/node/robocup_client_node.cpp"
  "src/${PROJECT_NAME}/receiver/node/receiver_node.cpp"
  "src/${PROJECT_NAME}/sender/node/sender_node.cpp"
  "src/${PROJECT_NAME}/robot_client/robot_client.cpp"
  "src/${PROJECT_NAME}/message_handler/message_handler.cpp"
  ${PROTO_SRC})
  
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>)

ament_target_dependencies(${PROJECT_NAME}
  keisan 
  Protobuf 
  rclcpp 
  kansei_interfaces
  shisen_interfaces
  tachimawari
  tachimawari_interfaces)

install(DIRECTORY "include" DESTINATION ".")

install(FILES ${PROTO_HEADER} DESTINATION "include/${PROJECT_NAME}")

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  RUNTIME DESTINATION "bin")

add_executable(client ${CMAKE_CURRENT_SOURCE_DIR}/examples/client.cpp)
target_link_libraries(client ${PROJECT_NAME})

install(TARGETS client
  DESTINATION "lib/${PROJECT_NAME}")

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(
  kansei_interfaces
  keisan 
  Protobuf
  rclcpp
  shisen_interfaces
  tachimawari
  tachimawari_interfaces)
ament_export_include_directories("include")
ament_export_libraries(${PROJECT_NAME})
ament_package()
