cmake_minimum_required(VERSION 3.5)
project(selfflow)

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
  "msg/Taskdata.msg"
)

 rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
 )


add_executable(selfflow_agent
 src/agentX.cpp
)

ament_target_dependencies(selfflow_agent
 "rclcpp"
)

get_default_rmw_implementation(rmw_implementation)
find_package("${rmw_implementation}" REQUIRED)
get_rmw_typesupport(typesupport_impls "${rmw_implementation}" LANGUAGE "cpp")

foreach(typesupport_impl ${typesupport_impls})
  rosidl_target_interfaces(selfflow_agent
    ${PROJECT_NAME} ${typesupport_impl}
  )
endforeach()

install(TARGETS selfflow_agent
  DESTINATION bin)


ament_package()
