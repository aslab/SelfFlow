// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from self_flow:msg/Bid.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__BID__TRAITS_HPP_
#define SELF_FLOW__MSG__DETAIL__BID__TRAITS_HPP_

#include "self_flow/msg/detail/bid__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<self_flow::msg::Bid>()
{
  return "self_flow::msg::Bid";
}

template<>
struct has_fixed_size<self_flow::msg::Bid>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<self_flow::msg::Bid>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<self_flow::msg::Bid>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SELF_FLOW__MSG__DETAIL__BID__TRAITS_HPP_
