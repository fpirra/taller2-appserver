# Paquetes necesarios
find_package(Threads REQUIRED)
find_package(libbsoncxx)
find_package(libmongocxx)

# Enable ExternalProject CMake module
include(ExternalProject)

# ----- Para code coverage
SET(CMAKE_CXX_FLAGS "-g -std=c++11 -O0 -Wall -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage --coverage")

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

# Agrego los archivos del server a testear
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/)
file(GLOB TESTS_DIR *.cpp)
FILE(GLOB SOURCE_PROGRAM_TO_TEST ../src/*.cpp)


# Borro el server.cpp, que contiene otro main, y entra en conflicto con el main del test
list(REMOVE_ITEM SOURCE_PROGRAM_TO_TEST ${CMAKE_CURRENT_SOURCE_DIR}/../src/server.cpp)

# Genero el ejecutable de los tests
add_executable(tests ${TESTS_DIR} ${SOURCE_PROGRAM_TO_TEST} )

# Linkeo las bibliotecas y agrego mas dependencias
include_directories ("${PROJECT_SOURCE_DIR}/mongoose-cpp")
add_dependencies (tests mongoose)
add_dependencies (tests spdlog)
link_directories(${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})
target_include_directories(tests PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS} PRIVATE ${LIBBSONCXX_INCLUDE_DIRS})
target_link_libraries (tests pthread)
target_link_libraries (tests mongoose)
target_link_libraries (tests jsoncpp)
target_link_libraries (tests ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (tests mongoose)
target_link_libraries (tests spdlog)
target_link_libraries (tests gcov)
target_link_libraries (tests ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES} Threads::Threads )

# Aca se ponen todas las carpetas con clases y codigo a testear
target_link_libraries(tests
    libgtest
    libgmock
)

install(TARGETS tests DESTINATION bin)



