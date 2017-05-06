# Set the base image to Ubuntu
FROM ubuntu:16.04

# Add repositories
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 0C49F3730359A14518585931BC711F9BA15703C6
RUN echo "deb [ arch=amd64,arm64 ] http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.4 multiverse" | tee /etc/apt/sources.list.d/mongodb-org-3.4.list

# Install required packages
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    git \
    g++ \
    libtool \
    autoconf \
    wget \
    pkg-config \
    libbson-1.0-0 \ 
    mongodb-org 

# Run mongod service
CMD ["service mongod start"] 

# Install MongoCxx driver
WORKDIR "/usr/libs/"
RUN git clone https://github.com/mongodb/mongo-c-driver.git
RUN cd mongo-c-driver ; git checkout 1.6.1 ; ./autogen.sh --with-libbson=bundled ; make ; make install

RUN git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1 
RUN cd mongo-cxx-driver/build ; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local .. ; make EP_mnmlstc_core ; make && make install
#----------------------

#Install jsoncpp
RUN git clone https://github.com/open-source-parsers/jsoncpp.git
RUN cd jsoncpp ; mkdir build ; cd build ; cmake .. ; make install
#----------------------

# Exports
RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"/usr/local/"

# Copy the proyect files into the container
COPY . /usr/src/appsvr
RUN cd /usr/src/appsvr/build/ ; cmake .. ; make 

# Run server
WORKDIR "/usr/src/appsvr/build/"
CMD ["./src/Server", "9900"]


