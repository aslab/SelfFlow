#!/usr/bin/env python3
#
# Copyright 2019 ROBOTIS CO., LTD.
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

import os

from ament_index_python.packages import get_package_prefix
from ament_index_python.packages import get_package_share_directory
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource

import launch.actions
import launch_ros.actions

TURTLEBOT3_MODEL = 'waffle'

def generate_launch_description():

	

	urdf_file_name = 'turtlebot3_' + TURTLEBOT3_MODEL + '.urdf'
	print('urdf_file_name : {}'.format(urdf_file_name))
	urdf = os.path.join(
		get_package_share_directory('turtlebot3_description'),
		'urdf',
		urdf_file_name)

	world = launch.substitutions.LaunchConfiguration('world')
	namespace = launch.substitutions.LaunchConfiguration('namespace')
	use_sim_time = launch.substitutions.LaunchConfiguration('use_sim_time', default='true')


	declare_world_cmd = launch.actions.DeclareLaunchArgument(
		'world',
		default_value=os.path.join(get_package_share_directory('self_flow'),
       		'worlds/house_ns.model'),
		description='Full path to world file to load')

	declare_namespace_cmd = launch.actions.DeclareLaunchArgument(
		'namespace',
		default_value='',
		description='Namespace')


	start_gazebo_cmd = launch.actions.ExecuteProcess(
		cmd=['gazebo', world,'-s', 'libgazebo_ros_init.so'],
        	output='screen')

	start_robot_cmd= launch_ros.actions.Node(
		package='robot_state_publisher',
		node_executable='robot_state_publisher',
		node_name='robot_state_publisher',
		node_namespace= namespace,
		output='screen',
		parameters=[{'use_sim_time': use_sim_time}],
		arguments=[urdf])

	start_selfflow_cmd = launch_ros.actions.Node(
		package='self_flow',
		node_executable='start_agent',
		node_name='agent_core',
		node_namespace= namespace,
		output='screen',
		parameters=[],
		arguments=['Arg'])

	ld = launch.LaunchDescription()

	ld.add_action(declare_world_cmd)
	ld.add_action(declare_namespace_cmd)
	ld.add_action(start_gazebo_cmd)
	ld.add_action(start_robot_cmd)
	#ld.add_action(start_selfflow_cmd)

	return ld
