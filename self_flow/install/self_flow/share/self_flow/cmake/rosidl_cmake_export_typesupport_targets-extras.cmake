# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_typesupport_introspection_c:self_flow__rosidl_typesupport_introspection_c;__rosidl_typesupport_introspection_cpp:self_flow__rosidl_typesupport_introspection_cpp")

# populate self_flow_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "self_flow::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'self_flow' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND self_flow_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()
