#include "Socket.h"

Socket:: Socket(){}

Socket:: Socket(int family, int socktype, int protocol){
    this->fd = socket(family,socktype,protocol);
}

bool Socket:: socket_bind_and_listen(const char* hostname, const char* servicename){
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
        Socket skt(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        setsockopt(skt.fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (bind(skt.fd, addr->ai_addr, addr->ai_addrlen) == 0) 
            is_connected = true;
    }
    freeaddrinfo(addr_list);
    
    if (!is_connected) {
		fprintf(stderr, "socket_bind_and_listen-->bind: %s\n", strerror(errno));
        return false;
    }

	if (listen(this->fd, 10) < 0) {
	    //socket_uninit(self);
        //this->~Socket;
		fprintf(stderr, "socket_bind_and_listen-->listen: %s\n", strerror(errno));
		return false;
	}
	return true;
}

int Socket:: socket_accept(Socket peer){
	int fd = -1;
    
	if ((peer.fd = accept(this->fd, NULL, NULL)) < 0) {
		fprintf(stderr, "socket_accept-->accept: %s\n", strerror(errno));
        return fd;
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
        printf("Error en getaddrinfo: %s\n", gai_strerror(s));
        return;
    }

    for (addr = results; addr != NULL && !is_connected ; addr = addr->ai_next) {
        this->fd = socket
        (addr->ai_family, addr->ai_socktype, addr->ai_protocol);

        if (this->fd == -1){
            printf("Error: %s\n", strerror(errno));
        }else{
            s = connect(this->fd, addr->ai_addr, addr->ai_addrlen);
            if ( s == -1 ){
                perror("Error");
                printf("%s\n",strerror(errno));
                close(this->fd);
            }
            is_connected = (s != -1);
        }
    }
    freeaddrinfo(results);

    if ( is_connected == false ){
        return;
    }
}

Socket:: ~Socket(){
    if (shutdown(this->fd, SHUT_RDWR) == -1) {
		fprintf(stderr, "socket_uninit-->shutdown: %s\n", strerror(errno));
    } 
    if (close(this->fd) == -1) {
		fprintf(stderr, "socket_uninit-->close: %s\n", strerror(errno));
    }
}
