// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from self_flow:msg/Bid.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__BID__FUNCTIONS_H_
#define SELF_FLOW__MSG__DETAIL__BID__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "self_flow/msg/rosidl_generator_c__visibility_control.h"

#include "self_flow/msg/detail/bid__struct.h"

/// Initialize msg/Bid message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * self_flow__msg__Bid
 * )) before or use
 * self_flow__msg__Bid__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
bool
self_flow__msg__Bid__init(self_flow__msg__Bid * msg);

/// Finalize msg/Bid message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
void
self_flow__msg__Bid__fini(self_flow__msg__Bid * msg);

/// Create msg/Bid message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * self_flow__msg__Bid__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
self_flow__msg__Bid *
self_flow__msg__Bid__create();

/// Destroy msg/Bid message.
/**
 * It calls
 * self_flow__msg__Bid__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
void
self_flow__msg__Bid__destroy(self_flow__msg__Bid * msg);


/// Initialize array of msg/Bid messages.
/**
 * It allocates the memory for the number of elements and calls
 * self_flow__msg__Bid__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
bool
self_flow__msg__Bid__Sequence__init(self_flow__msg__Bid__Sequence * array, size_t size);

/// Finalize array of msg/Bid messages.
/**
 * It calls
 * self_flow__msg__Bid__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
void
self_flow__msg__Bid__Sequence__fini(self_flow__msg__Bid__Sequence * array);

/// Create array of msg/Bid messages.
/**
 * It allocates the memory for the array and calls
 * self_flow__msg__Bid__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
self_flow__msg__Bid__Sequence *
self_flow__msg__Bid__Sequence__create(size_t size);

/// Destroy array of msg/Bid messages.
/**
 * It calls
 * self_flow__msg__Bid__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_self_flow
void
self_flow__msg__Bid__Sequence__destroy(self_flow__msg__Bid__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SELF_FLOW__MSG__DETAIL__BID__FUNCTIONS_H_
