cmake_minimum_required(VERSION 3.8)
project(actions_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(simple_action_server src/simple_action_server.cpp)
ament_target_dependencies(simple_action_server
rclcpp
rclcpp_action
example_interfaces
)

# add_executable(simple_action_client src/simple_action_client.cpp)
# ament_target_dependencies(simple_action_client
# rclcpp
# rclcpp_action
# example_interfaces
# )

install(TARGETS
simple_action_server

DESTINATION lib/${PROJECT_NAME}
)

ament_package()
