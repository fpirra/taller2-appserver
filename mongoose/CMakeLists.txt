cmake_minimum_required(VERSION 2.8.4)
project(mongoose)

set (SOURCES
    mongoose.c
    )

# Compiling library
add_library (mongoose ${SOURCES})
