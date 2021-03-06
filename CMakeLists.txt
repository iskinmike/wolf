# Copyright 2018, mike at myasnikov.mike@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

project ( wolf CXX )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -g")

set(SOURCES
    src/main.cpp
    src/preconstruction_class.hpp
    src/world.hpp
    src/world.cpp
    src/color.hpp
    src/game_field.hpp
    src/player.hpp
    src/view_screen.hpp
)

set(LIBS
    SDL2
    pthread
)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries ( ${PROJECT_NAME} ${LIBS})

target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE
     ${CMAKE_SOURCE_DIR}
)
