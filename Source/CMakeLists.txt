cmake_minimum_required(VERSION 3.3)
project(Idea)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES IdeaCipher.c IDEA.c IDEA.h KeyCreation.c KeyCreation.h Round.c Round.h)
add_executable(Idea ${SOURCE_FILES})