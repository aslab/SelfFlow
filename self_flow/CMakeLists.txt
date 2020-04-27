cmake_minimum_required(VERSION 3.5)
project(self_flow)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rmw_implementation_cmake REQUIRED)


set(msg_files
  "msg/TaskAuction.msg"
  "msg/TaskBid.msg"
  "msg/TaskAssign.msg"
)

 rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
 )


add_executable(agent_test
 src/test.cpp
)

target_include_directories(agent_test PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)



ament_target_dependencies(agent_test
 "rclcpp"
)

get_default_rmw_implementation(rmw_implementation)
find_package("${rmw_implementation}" REQUIRED)
get_rmw_typesupport(typesupport_impls "${rmw_implementation}" LANGUAGE "cpp")

foreach(typesupport_impl ${typesupport_impls})
  rosidl_target_interfaces(agent_test
    ${PROJECT_NAME} ${typesupport_impl}
  )
endforeach()

install(TARGETS agent_test
  EXPORT EXPORT_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})


ament_package()
