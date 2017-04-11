# UnderFy Appserver

UnderFy Appserver es una aplicación escrita en C++, con el propósito de brindar una interfaz para la comunicación de los
diferentes clientes que se conecten a la misma. Para la interfaz de comunicación se utilizará
Restful API [1], que definirá la forma de las solicitudes y respuestas de los diferentes servicios
que brindará el servidor.

El objetivo principal de esta aplicación es la de administración del contenido multimedia del
sistema.

# Desarrollada por:

96626 - Maria Florencia Prado 

87796 - Gabriel La Torre

89992 - Matias Cerrotta

95178 - Francisco Pirra


# API para interactuar con el server

Pedir cancion:

>  "GET", "appsvr/song", (header: api_token, parametros: id_song)

Agregar cancion:

>  "PUT", "appsvr/song", (header: api_token, parametros: id_song, song_file)

Borrar cancion: 

>  "DELETE", "appsvr/song", (header: api_token, parametros: id_song)

# Instalación

## Dependencias

### Instalacion MongoDB comunidad

Agregar la clave:

> sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 0C49F3730359A14518585931BC711F9BA15703C6

Luego, segun la version de Ubuntu:

#### Ubuntu 12.04

> echo "deb [ arch=amd64 ] http://repo.mongodb.org/apt/ubuntu precise/mongodb-org/3.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.4.list

#### Ubuntu 14.04

> echo "deb [ arch=amd64 ] http://repo.mongodb.org/apt/ubuntu trusty/mongodb-org/3.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.4.list

#### Ubuntu 16.04

> echo "deb [ arch=amd64,arm64 ] http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.4 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-3.4.list

Luego, actualizar los paquetes

> sudo apt-get update

Instalar mongoDB, version comunidad:

> sudo apt-get install -y mongodb-org

Iniciar el demonio `mongod`. Esto es vital para que funcione el server, ya que es el servidor de mongoDB

> sudo service mongod start

### Instalacion mongocxx driver

Una vez realizada la instalacion de mongoDB, en su version comunidad, procederemos a instalar el driver de mongocxx, para poder utilizar con C++

Primero, instalamos el driver para C:

> git clone https://github.com/mongodb/mongo-c-driver.git

> cd mongo-c-driver

> git checkout 1.6.1  # Para buildear la version 1.6.1 que necesita el driver 

> ./autogen.sh --with-libbson=bundled

> make

> sudo make install

Luego el driver para C++:

> git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1

> cd mongo-cxx-driver/build

> cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..

> sudo make EP_mnmlstc_core

> make && sudo make install

Con estos pasos tendrian que estar listas las dependencias necesarias, por cualquier duda el link a la pagina de instalacion del driver es: https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/installation/

### Instalacion JsonCpp

Bajar el repositorio oficial

> git clone https://github.com/open-source-parsers/jsoncpp.git

Luego ejecutar:

> mkdir build 

> cd build 

> cmake .. 

> sudo make install

Para tener instalado en el sistema, las librerias de Json

## Compilar y correr el server

Crear el directorio `build`, en la carpeta raiz del proyecto

> mkdir build

Luego entrar dentro, y ejecutar `cmake`:

> cd build

> cmake ..

Por ultimo, compilar usando `make`:

> make

### Correr el server

> cd src

> ./Server <puerto>



