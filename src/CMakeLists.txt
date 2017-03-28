cmake_minimum_required(VERSION 2.8.4)

# Generar el ejecutable
add_executable (Server server.cpp)

# Añadir dependencias a otras acciones
add_dependencies (Server mongoose)

# Agrego el directorio donde estan los headers 
include_directories ("${PROJECT_SOURCE_DIR}/mongoose-cpp")

# Linkeo para generar el binario, server, en base a sus dependencias con otros binarios
target_link_libraries (Server mongoose)
