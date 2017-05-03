# Set the base image to Ubuntu
FROM ubuntu:16.04

# Install required packages
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    git \
    g++ \
    wget \
#----------------------

#Install MongoDB
RUN echo "deb [ arch=amd64,arm64 ] http://repo.mongodb.org/apt/ubuntu xenial/mongodb-org/3.4 multiverse" | tee /etc/apt/sources.list.d/mongodb-org-3.4.list
RUN apt-get update ; apt-get install -y mongodb-org ; service mongod start 
#----------------------

#Install MongoCxx
RUN wget https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/curlpp/curlpp-0.7.3.tar.gz
RUN tar zxf curlpp-0.7.3.tar.gz ; cd curlpp-0.7.3 ; ./configure ; make ; make install
RUN git clone https://github.com/mongodb/mongo-c-driver.git
RUN cd mongo-c-driver ; git checkout 1.6.1 ; ./autogen.sh --with-libbson=bundled ; make ; make install
RUN git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1
RUN cd mongo-cxx-driver/build ; cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
RUN make EP_mnmlstc_core ; make ; make install

#----------------------

#Install jsoncpp
RUN git clone https://github.com/open-source-parsers/jsoncpp.git
RUN cd jsoncpp ; mkdir build ; cd build ; cmake .. ; make install
#----------------------

# Copy the proyect files into the container
COPY . /usr/src/appsvr
RUN cd /usr/src/appsvr/build/ ; cmake .. ; make ;

# Run server
CMD ["./src/Server 9900"]


