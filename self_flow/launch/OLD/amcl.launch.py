# Copyright (c) 2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

""" This is all-in-one launch script intended for use by nav2 developers. """

import os

from ament_index_python.packages import get_package_prefix
from ament_index_python.packages import get_package_share_directory
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from nav2_common.launch import RewrittenYaml

import launch.actions
import launch_ros.actions


def generate_launch_description():
    # Get the launch directory
    launch_dir = os.path.join(get_package_share_directory('self_flow'), 'launch')

    # Create the launch configuration variables
    params_file = launch.substitutions.LaunchConfiguration('params')
    map_yaml_file = launch.substitutions.LaunchConfiguration('map')
    namespace = launch.substitutions.LaunchConfiguration('namespace')

    # Create our own temporary YAML files that include the following parameter substitutions
    param_substitutions = {
        'yaml_filename': map_yaml_file
    }
    configured_params = RewrittenYaml(
        source_file=params_file, rewrites=param_substitutions, convert_types=True)

    # Declare the launch arguments
    declare_map_yaml_cmd = launch.actions.DeclareLaunchArgument(
        'map',
        default_value= os.path.join(get_package_share_directory('self_flow'), 'launch/turtlebot3_world.yaml'),
        description='Full path to map file to load')

    declare_params_file_cmd = launch.actions.DeclareLaunchArgument(
        'params',
        default_value=[launch.substitutions.ThisLaunchFileDir(), '/nav2_params.yaml'],
        description='Full path to the ROS2 parameters file to use for all launched nodes')

    declare_namespace_cmd = launch.actions.DeclareLaunchArgument(
        'namespace',
        default_value='',
        description='Namespace')



    stdout_linebuf_envvar = launch.actions.SetEnvironmentVariable(
        'RCUTILS_CONSOLE_STDOUT_LINE_BUFFERED', '1')

    # Specify the actions

    start_map_server_cmd = launch_ros.actions.Node(
        package='nav2_map_server',
        node_executable='map_server',
        node_name='map_server',
        output='screen',
        parameters=[configured_params])


    start_localizer_cmd = launch_ros.actions.Node(
        package='nav2_amcl',
        node_executable='amcl',
        node_name='amcl',
	node_namespace= namespace,
        output='screen',
        parameters=[configured_params])


    # Create the launch description and populate
    ld = launch.LaunchDescription()

    # Declare the launch options
    ld.add_action(declare_map_yaml_cmd)
    ld.add_action(declare_params_file_cmd)
    ld.add_action(declare_namespace_cmd)

    # Set environment variables
    ld.add_action(stdout_linebuf_envvar)

    ld.add_action(start_map_server_cmd)
    ld.add_action(start_localizer_cmd)

    return ld
