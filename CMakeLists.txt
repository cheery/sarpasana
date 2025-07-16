cmake_minimum_required(VERSION 3.10...3.18)
project(sarpasana)

add_subdirectory(pybind11)
add_subdirectory(yoga/yoga)
pybind11_add_module(sarpasana src/sarpasana.cpp)

target_compile_definitions(sarpasana
                           PRIVATE VERSION_INFO=${SARPASANA_VERSION_INFO})
target_link_libraries(sarpasana PUBLIC yogacore)
