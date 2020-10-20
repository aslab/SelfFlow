// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from self_flow:msg/Task.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__TASK__STRUCT_HPP_
#define SELF_FLOW__MSG__DETAIL__TASK__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__self_flow__msg__Task __attribute__((deprecated))
#else
# define DEPRECATED__self_flow__msg__Task __declspec(deprecated)
#endif

namespace self_flow
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Task_
{
  using Type = Task_<ContainerAllocator>;

  explicit Task_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->agent = "";
      this->status = 0;
    }
  }

  explicit Task_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : id(_alloc),
    agent(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->agent = "";
      this->status = 0;
    }
  }

  // field types and members
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _id_type id;
  using _agent_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _agent_type agent;
  using _status_type =
    uint8_t;
  _status_type status;

  // setters for named parameter idiom
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__agent(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->agent = _arg;
    return *this;
  }
  Type & set__status(
    const uint8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    self_flow::msg::Task_<ContainerAllocator> *;
  using ConstRawPtr =
    const self_flow::msg::Task_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<self_flow::msg::Task_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<self_flow::msg::Task_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      self_flow::msg::Task_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<self_flow::msg::Task_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      self_flow::msg::Task_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<self_flow::msg::Task_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<self_flow::msg::Task_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<self_flow::msg::Task_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__self_flow__msg__Task
    std::shared_ptr<self_flow::msg::Task_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__self_flow__msg__Task
    std::shared_ptr<self_flow::msg::Task_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Task_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->agent != other.agent) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    return true;
  }
  bool operator!=(const Task_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Task_

// alias to use template instance with default allocator
using Task =
  self_flow::msg::Task_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace self_flow

#endif  // SELF_FLOW__MSG__DETAIL__TASK__STRUCT_HPP_
