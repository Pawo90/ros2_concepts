cmake_minimum_required(VERSION 3.8)
project(services_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(simple_srv_server src/simple_srv_server.cpp)
ament_target_dependencies(simple_srv_server
rclcpp
example_interfaces
)

add_executable(simple_srv_client src/simple_srv_client.cpp)
ament_target_dependencies(simple_srv_client
rclcpp
example_interfaces
)

install(TARGETS
simple_srv_server
simple_srv_client
DESTINATION lib/${PROJECT_NAME}
)

ament_package()
