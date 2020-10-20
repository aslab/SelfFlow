// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from self_flow:msg/Bid.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__BID__STRUCT_H_
#define SELF_FLOW__MSG__DETAIL__BID__STRUCT_H_

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

// Struct defined in msg/Bid in the package self_flow.
typedef struct self_flow__msg__Bid
{
  rosidl_runtime_c__String id;
  rosidl_runtime_c__String agent;
  double utility;
} self_flow__msg__Bid;

// Struct for a sequence of self_flow__msg__Bid.
typedef struct self_flow__msg__Bid__Sequence
{
  self_flow__msg__Bid * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} self_flow__msg__Bid__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SELF_FLOW__MSG__DETAIL__BID__STRUCT_H_
