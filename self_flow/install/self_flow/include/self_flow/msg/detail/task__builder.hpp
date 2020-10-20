// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from self_flow:msg/Task.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__TASK__BUILDER_HPP_
#define SELF_FLOW__MSG__DETAIL__TASK__BUILDER_HPP_

#include "self_flow/msg/detail/task__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace self_flow
{

namespace msg
{

namespace builder
{

class Init_Task_status
{
public:
  explicit Init_Task_status(::self_flow::msg::Task & msg)
  : msg_(msg)
  {}
  ::self_flow::msg::Task status(::self_flow::msg::Task::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::self_flow::msg::Task msg_;
};

class Init_Task_agent
{
public:
  explicit Init_Task_agent(::self_flow::msg::Task & msg)
  : msg_(msg)
  {}
  Init_Task_status agent(::self_flow::msg::Task::_agent_type arg)
  {
    msg_.agent = std::move(arg);
    return Init_Task_status(msg_);
  }

private:
  ::self_flow::msg::Task msg_;
};

class Init_Task_id
{
public:
  Init_Task_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Task_agent id(::self_flow::msg::Task::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Task_agent(msg_);
  }

private:
  ::self_flow::msg::Task msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::self_flow::msg::Task>()
{
  return self_flow::msg::builder::Init_Task_id();
}

}  // namespace self_flow

#endif  // SELF_FLOW__MSG__DETAIL__TASK__BUILDER_HPP_
