cmake_minimum_required(VERSION 3.5)
project(self_flow_core)

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
find_package(std_msgs REQUIRED)
#find_package(geometry_msgs REQUIRED)

set(library_name self_flow_agent)

set(msg_files
  "msg/Task.msg"
  "msg/Bid.msg"
)

 rosidl_generate_interfaces(${PROJECT_NAME}
   ${msg_files}
 )


#add_executable(start_agent
# src/Start.cpp
#)

add_library(${library_name} SHARED
  src/Agent.cpp
)


target_include_directories(${library_name} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)



ament_target_dependencies(${library_name}
 "rclcpp"
 "std_msgs"
# "geometry_msgs"
)

get_default_rmw_implementation(rmw_implementation)
find_package("${rmw_implementation}" REQUIRED)
get_rmw_typesupport(typesupport_impls "${rmw_implementation}" LANGUAGE "cpp")

foreach(typesupport_impl ${typesupport_impls})
  rosidl_target_interfaces(${library_name}
    ${PROJECT_NAME} ${typesupport_impl}
  )
endforeach()

install( TARGETS ${library_name}
  EXPORT EXPORT_${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
