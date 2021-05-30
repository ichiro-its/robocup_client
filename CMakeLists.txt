cmake_minimum_required(VERSION 3.5)

project(webots_controller)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(musen REQUIRED)
find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER include/webots_controller/messages.proto)

add_library(${PROJECT_NAME}
  "src/coba.cpp" 
  ${PROTO_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>)

ament_target_dependencies(${PROJECT_NAME} 
  musen Protobuf)

install(DIRECTORY "include" DESTINATION ".")

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  RUNTIME DESTINATION "bin")

add_executable(coba ${CMAKE_CURRENT_SOURCE_DIR}/src/coba.cpp)
target_link_libraries(coba ${PROJECT_NAME})

# add_executable(client "src/client.cpp" ${PROTO_SRC})
# target_include_directories(client PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_link_libraries(client ${PROJECT_NAME}
#   protobuf::libprotobuf
# )

install(TARGETS coba
  DESTINATION "lib/${PROJECT_NAME}")

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(musen Protobuf)
ament_export_include_directories("include")
ament_export_libraries(${PROJECT_NAME})
ament_package()
