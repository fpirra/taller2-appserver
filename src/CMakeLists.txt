cmake_minimum_required(VERSION 2.8.4)

# Generar el ejecutable
add_executable (Server server.cpp)
add_executable (testDB dbHandler.cpp)

# Agrego flags a cada ejecutable
target_compile_options(testDB PRIVATE -std=c++11 )

# Busco los paquetes necesarios para compilar
find_package(libbsoncxx)
find_package(libmongocxx)
find_package(Threads)

# Añadir dependencias a otras acciones
add_dependencies (Server mongoose)

# Agrego el directorio donde estan los headers 
include_directories ("${PROJECT_SOURCE_DIR}/mongoose-cpp")
link_directories(${LIBMONGOCXX_LIBRARY_DIRS} ${LIBBSONCXX_LIBRARY_DIRS})
target_include_directories(testDB PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS} PRIVATE ${LIBBSONCXX_INCLUDE_DIRS})

# Linkeo para generar el binario, server, en base a sus dependencias con otros binarios
target_link_libraries (Server mongoose)
target_link_libraries(testDB PRIVATE ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES} Threads::Threads )




