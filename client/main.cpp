#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

int main() {
    int sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    
    if( sockfd < 0 ) {
        std::cout<< "Error Socket:" << std::strerror(errno);
        exit( 1 );
    }

    struct sockaddr_in addr;
    std::memset( &addr, 0, sizeof( struct sockaddr_in ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( 1234 );
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    
    if( connect( sockfd, ( struct sockaddr *)&addr, sizeof( struct sockaddr_in ) ) < 0 ) {
        std::cout<< "Error connect:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }
    
    char send_str[256];
    std::sprintf( send_str, "ClientHello" );
    if( send( sockfd, send_str, sizeof( send_str ), 0 ) < 0 ) {
        std::cout<< "Error send:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }
    
    char recive_str[256];
    if( recv( sockfd, recive_str, sizeof( recive_str ), 0 ) < 0 ) {
        std::cout<< "Error recv:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }
    std::cout << recive_str << "\n";

    close( sockfd );
    return 0;
}
