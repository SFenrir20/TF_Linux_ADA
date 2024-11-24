cmake_minimum_required(VERSION 3.29)
project(Prueba_Boost)

set(CMAKE_CXX_STANDARD 20)

add_executable(TF_Linux_EDA main.cpp
        Ciudadano.h
        CuckooHashing.h
        menu.cpp
        menu.h
        CuckooHashing.cpp
        main.cpp
        main.cpp
        main.cpp
        server.cpp
)

target_link_libraries(TF_Linux_EDA ${Boost_LIBRARIES})
