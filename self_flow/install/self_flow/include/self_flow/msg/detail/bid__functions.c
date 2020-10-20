// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from self_flow:msg/Bid.idl
// generated code does not contain a copyright notice
#include "self_flow/msg/detail/bid__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `id`
// Member `agent`
#include "rosidl_runtime_c/string_functions.h"

bool
self_flow__msg__Bid__init(self_flow__msg__Bid * msg)
{
  if (!msg) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__init(&msg->id)) {
    self_flow__msg__Bid__fini(msg);
    return false;
  }
  // agent
  if (!rosidl_runtime_c__String__init(&msg->agent)) {
    self_flow__msg__Bid__fini(msg);
    return false;
  }
  // utility
  return true;
}

void
self_flow__msg__Bid__fini(self_flow__msg__Bid * msg)
{
  if (!msg) {
    return;
  }
  // id
  rosidl_runtime_c__String__fini(&msg->id);
  // agent
  rosidl_runtime_c__String__fini(&msg->agent);
  // utility
}

self_flow__msg__Bid *
self_flow__msg__Bid__create()
{
  self_flow__msg__Bid * msg = (self_flow__msg__Bid *)malloc(sizeof(self_flow__msg__Bid));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(self_flow__msg__Bid));
  bool success = self_flow__msg__Bid__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
self_flow__msg__Bid__destroy(self_flow__msg__Bid * msg)
{
  if (msg) {
    self_flow__msg__Bid__fini(msg);
  }
  free(msg);
}


bool
self_flow__msg__Bid__Sequence__init(self_flow__msg__Bid__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  self_flow__msg__Bid * data = NULL;
  if (size) {
    data = (self_flow__msg__Bid *)calloc(size, sizeof(self_flow__msg__Bid));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = self_flow__msg__Bid__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        self_flow__msg__Bid__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
self_flow__msg__Bid__Sequence__fini(self_flow__msg__Bid__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      self_flow__msg__Bid__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

self_flow__msg__Bid__Sequence *
self_flow__msg__Bid__Sequence__create(size_t size)
{
  self_flow__msg__Bid__Sequence * array = (self_flow__msg__Bid__Sequence *)malloc(sizeof(self_flow__msg__Bid__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = self_flow__msg__Bid__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
self_flow__msg__Bid__Sequence__destroy(self_flow__msg__Bid__Sequence * array)
{
  if (array) {
    self_flow__msg__Bid__Sequence__fini(array);
  }
  free(array);
}
