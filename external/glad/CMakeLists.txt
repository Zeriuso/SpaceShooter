cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

project(glad)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include/)
