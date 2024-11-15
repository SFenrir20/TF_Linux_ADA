cmake_minimum_required(VERSION 3.29)
project(Prueba_Boost)

set(CMAKE_CXX_STANDARD 20)

set(BOOST_ROOT "/home/fenrirdev/boost_1_86_0")

find_package(Boost 1.86.0 COMPONENTS iostreams REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(TF_Linux_EDA main.cpp
        Ciudadano.h
        CuckooHashing.h
        menu.cpp
        menu.h
        CuckooHashing.cpp
)

target_link_libraries(TF_Linux_EDA ${Boost_LIBRARIES})
