 cmake_minimum_required(VERSION 2.8.4)

# Agrego todos los .h y .cpp del proyecto
file(GLOB SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Generar el ejecutable
add_executable (Server ${SOURCES} )

# Agrego flags 
SET(CMAKE_CXX_FLAGS "-O0 -std=c++11 -Wall ")
SET(CMAKE_C_FLAGS "-O0 -std=c++11 -Wall -W ")

# Busco los paquetes necesarios para compilar
find_package(libbsoncxx)
find_package(libmongocxx)
find_package(Threads)

# Añadir dependencias a otras acciones
add_dependencies (Server mongoose)
add_dependencies (Server spdlog)

# Agrego el directorio donde estan los headers 
include_directories ("${PROJECT_SOURCE_DIR}/mongoose-cpp")
include_directories ("${PROJECT_SOURCE_DIR}/spdlog")
include_directories ("${PROJECT_SOURCE_DIR}/src")
link_directories(${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})
target_include_directories(Server PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS} PRIVATE ${LIBBSONCXX_INCLUDE_DIRS})

# Linkeo para generar el binario, server, en base a sus dependencias con otros binarios
target_link_libraries (Server mongoose)
target_link_libraries (Server spdlog)
target_link_libraries (Server ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES} Threads::Threads )




