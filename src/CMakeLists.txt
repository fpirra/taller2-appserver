cmake_minimum_required(VERSION 2.8.4)

# Generar el ejecutable
add_executable (Server server.c)

# Añadir dependencias a otras acciones
add_dependencies (Server mongoose)

target_link_libraries (Server mongoose)
