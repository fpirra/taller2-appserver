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

# Instalación

## Docker para linux

### Para Ubuntu

https://www.docker.com/docker-ubuntu

### Para Mint

http://linuxbsdos.com/2016/12/13/how-to-install-docker-and-run-docker-containers-on-linux-mint-1818-1/

## Instalar docker-compose

En linux Mint:
>sudo apt install docker-c

# MongoDB

Comandos de https://hub.docker.com/_/mongo/

> sudo docker pull mongo sudo docker run --name some-mongo -d mongo

# Mongoose

##Documentación y bibliografía

https://github.com/cesanta/mongoose/blob/master/examples/examples.mk
https://github.com/cesanta/mongoose/tree/master/examples/simplest_web_server
https://github.com/cesanta/mongoose
https://docs.cesanta.com/mongoose/master/#/overview/
https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/installation/

# Instalar el servidor

cmake lee los archivos CMakeLists.txt al lanzar el comando:

> cmake .

Siendo . la ubicación actual. Generando así archivos Makefile que tienen lo necesario para poder crear el proyecto con el comando

> make

# Correr servidor

> cd src
> ./Server

# Json Server

Documentación en https://github.com/clue/docker-json-server

> docker run -d -p 9090:80 -v <path absoluto>/articles.json:/data/db.json clue/json-server

Navegar a localhost:9090


#TODO

* Hacer que el ejecutable se cree en la raíz del proyecto

