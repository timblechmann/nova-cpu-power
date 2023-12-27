cmake_minimum_required(VERSION 3.16)

project(nova-cpu-power VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

add_custom_target(nova_cpu_power_project_files SOURCES
    .pre-commit-config.yaml
    _clang-format
    conanfile.txt
)


find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Fmt)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(daemon)
add_subdirectory(gui)
