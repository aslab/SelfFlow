// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from self_flow:msg/Task.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__TASK__STRUCT_H_
#define SELF_FLOW__MSG__DETAIL__TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'id'
// Member 'agent'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/Task in the package self_flow.
typedef struct self_flow__msg__Task
{
  rosidl_runtime_c__String id;
  rosidl_runtime_c__String agent;
  uint8_t status;
} self_flow__msg__Task;

// Struct for a sequence of self_flow__msg__Task.
typedef struct self_flow__msg__Task__Sequence
{
  self_flow__msg__Task * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} self_flow__msg__Task__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SELF_FLOW__MSG__DETAIL__TASK__STRUCT_H_
