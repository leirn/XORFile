cmake_minimum_required(VERSION 2.6)
project (XORFile)

file( GLOB_RECURSE SOURCE_FILES src/* )

add_executable (XORFile ${SOURCE_FILES})
