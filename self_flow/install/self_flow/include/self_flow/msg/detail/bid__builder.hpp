// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from self_flow:msg/Bid.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__BID__BUILDER_HPP_
#define SELF_FLOW__MSG__DETAIL__BID__BUILDER_HPP_

#include "self_flow/msg/detail/bid__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace self_flow
{

namespace msg
{

namespace builder
{

class Init_Bid_utility
{
public:
  explicit Init_Bid_utility(::self_flow::msg::Bid & msg)
  : msg_(msg)
  {}
  ::self_flow::msg::Bid utility(::self_flow::msg::Bid::_utility_type arg)
  {
    msg_.utility = std::move(arg);
    return std::move(msg_);
  }

private:
  ::self_flow::msg::Bid msg_;
};

class Init_Bid_agent
{
public:
  explicit Init_Bid_agent(::self_flow::msg::Bid & msg)
  : msg_(msg)
  {}
  Init_Bid_utility agent(::self_flow::msg::Bid::_agent_type arg)
  {
    msg_.agent = std::move(arg);
    return Init_Bid_utility(msg_);
  }

private:
  ::self_flow::msg::Bid msg_;
};

class Init_Bid_id
{
public:
  Init_Bid_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bid_agent id(::self_flow::msg::Bid::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Bid_agent(msg_);
  }

private:
  ::self_flow::msg::Bid msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::self_flow::msg::Bid>()
{
  return self_flow::msg::builder::Init_Bid_id();
}

}  // namespace self_flow

#endif  // SELF_FLOW__MSG__DETAIL__BID__BUILDER_HPP_
