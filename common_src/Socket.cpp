#include "Socket.h"
#include <iostream>
#include <netdb.h>
#include <errno.h>
#include "AcceptorClosedException.h"
#include "SocketException.h"

Socket:: Socket(){}

Socket:: Socket
(const int& family,const int& socktype,const int& protocol){
    socket_init(family,socktype,protocol);
}

void Socket:: socket_init(int family,int socktype,int protocol){
    this->fd = socket(family,socktype,protocol);
}

bool Socket:: bind_and_listen(const char* hostname, const char* servicename){
    bool is_connected = false;
	int val = 1;
	struct addrinfo *addr, *addr_list;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(hostname,servicename,&hints,&addr_list);

	for (addr = addr_list; addr && !is_connected; addr = addr->ai_next) {
        socket_init(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (bind(this->fd, addr->ai_addr, addr->ai_addrlen) == 0) 
            is_connected = true;
    }
    freeaddrinfo(addr_list);

    if (!is_connected) {
        std::cout<<"socket_bind_and_listen-->bind: "<<strerror(errno)<<std::endl
        <<"Presione la tecla 'q' para finalizar"<<std::endl;
        throw SocketException();
    }

	if (listen(this->fd, 10) < 0) {
        std::cout<<"socket_bind_and_listen-->listen: "<<strerror(errno)<<std::endl
        <<"Presione la tecla 'q' para finalizar"<<std::endl;;
        throw SocketException();
	}

	return true;
}

int Socket:: socket_accept(Socket* peer){
	int fd = -1;
    
	if ((peer->fd = accept(this->fd, NULL, NULL)) == -1) {
        if (errno == EINVAL){
            throw AcceptorClosedException();
        }else{
            std::cout<<"Error: "<<strerror(errno)<<std::endl;
            throw SocketException();
        }
	}
    
    fd = 0;
	return fd;
}

void Socket:: socket_connect(const char* hostname, const char* servicename){
	this->fd=0;
    
    bool is_connected = false;
    int s = 0;
    struct addrinfo hints;
    struct addrinfo* results;
    struct addrinfo* addr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(hostname,servicename,&hints,&results);

    if (s != 0) {
        std::cout<<"Error en getaddrinfo: "<<gai_strerror(s)<<std::endl;
        throw SocketException();
    }

    for (addr = results; addr != NULL && !is_connected ; addr = addr->ai_next) {
        this->fd = socket
        (addr->ai_family, addr->ai_socktype, addr->ai_protocol);

        if (this->fd == -1){
            std::cout<<"Error: "<<strerror(errno)<<std::endl;
            throw SocketException();
        }else{
            s = connect(this->fd, addr->ai_addr, addr->ai_addrlen);
            if ( s == -1 ){               
                close(this->fd);
                std::cout<<"Error: "<<strerror(errno)<<std::endl;
                throw SocketException();
            }
            is_connected = (s != -1);
        }
    }
    freeaddrinfo(results);

    if ( is_connected == false ){
        return;
    }
}

void Socket:: socket_close(){
    shutdown(this->fd, SHUT_RDWR);
    close(this->fd);
}

ssize_t Socket:: socket_send(const char* msg,int length){
    int remaining_bytes = length;
    int total_bytes_sent = 0;

    while (total_bytes_sent < length) {
        ssize_t bytes = send(this->fd, 
                            &msg[total_bytes_sent], 
                             remaining_bytes, MSG_NOSIGNAL);
        if (bytes == 0) break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_sent;
}

int Socket:: socket_receive(int length, char* buffer){
    if (length == 0){ return 0; }
    int remaining_bytes = length;
    int total_bytes_received = 0;

    while (total_bytes_received < length) {
        ssize_t bytes = recv(this->fd, &buffer[total_bytes_received],
                        remaining_bytes, 0);
        if (bytes == 0) break;
        
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    return total_bytes_received;
}

void Socket:: socket_shutdown(){
    shutdown(this->fd, SHUT_WR);
}

Socket::Socket(Socket &&other){
    this->fd = std::move(other.fd);
    other.fd = 0;
}

Socket& Socket::operator=(Socket&& other){
    if (this == &other) return *this;
    this->fd = std::move(other.fd);
    other.fd = 0;
    return *this;
}

Socket:: ~Socket(){
   if (this->fd != -1){
        shutdown(this->fd, SHUT_RDWR);
        close(this->fd);
   }
   this->fd = -1;
}
