// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from self_flow:msg/Bid.idl
// generated code does not contain a copyright notice

#ifndef SELF_FLOW__MSG__DETAIL__BID__STRUCT_HPP_
#define SELF_FLOW__MSG__DETAIL__BID__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__self_flow__msg__Bid __attribute__((deprecated))
#else
# define DEPRECATED__self_flow__msg__Bid __declspec(deprecated)
#endif

namespace self_flow
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Bid_
{
  using Type = Bid_<ContainerAllocator>;

  explicit Bid_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->agent = "";
      this->utility = 0.0;
    }
  }

  explicit Bid_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : id(_alloc),
    agent(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->agent = "";
      this->utility = 0.0;
    }
  }

  // field types and members
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _id_type id;
  using _agent_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _agent_type agent;
  using _utility_type =
    double;
  _utility_type utility;

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
  Type & set__utility(
    const double & _arg)
  {
    this->utility = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    self_flow::msg::Bid_<ContainerAllocator> *;
  using ConstRawPtr =
    const self_flow::msg::Bid_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<self_flow::msg::Bid_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<self_flow::msg::Bid_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      self_flow::msg::Bid_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<self_flow::msg::Bid_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      self_flow::msg::Bid_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<self_flow::msg::Bid_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<self_flow::msg::Bid_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<self_flow::msg::Bid_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__self_flow__msg__Bid
    std::shared_ptr<self_flow::msg::Bid_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__self_flow__msg__Bid
    std::shared_ptr<self_flow::msg::Bid_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Bid_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->agent != other.agent) {
      return false;
    }
    if (this->utility != other.utility) {
      return false;
    }
    return true;
  }
  bool operator!=(const Bid_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Bid_

// alias to use template instance with default allocator
using Bid =
  self_flow::msg::Bid_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace self_flow

#endif  // SELF_FLOW__MSG__DETAIL__BID__STRUCT_HPP_
