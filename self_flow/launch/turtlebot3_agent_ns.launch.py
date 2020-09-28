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
#
# Authors: Darby Lim

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir
from launch.actions import ExecuteProcess
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

TURTLEBOT3_MODEL = 'waffle' 

def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    
    urdf_file_name = 'turtlebot3_' + TURTLEBOT3_MODEL + '.urdf'
    print('urdf_file_name : {}'.format(urdf_file_name))
    urdf = os.path.join(
        get_package_share_directory('turtlebot3_description'),
        'urdf',
        urdf_file_name)

    world = os.path.join(get_package_share_directory('self_flow'), 'worlds', 'test_ns.model' )


    return LaunchDescription([


        ExecuteProcess(
            cmd=['gazebo', '--verbose', world , '-s', 'libgazebo_ros_init.so'],
            output='screen'),

	DeclareLaunchArgument(
        'namespace',
        default_value='',
        description='Namespace'),

 
        Node(
            package='robot_state_publisher',
            node_executable='robot_state_publisher',
            node_name='robot_state_publisher',
	    node_namespace= LaunchConfiguration('namespace'),
            output='screen',
            parameters=[{'use_sim_time': use_sim_time}],
            arguments=[urdf]),

	Node(
            package='self_flow',
            node_executable='start_agent',
          # node_name='agent_core',
	    node_namespace= LaunchConfiguration('namespace'),
            output='screen',
            parameters=[],
            arguments=['Argument']),
	





    ])
