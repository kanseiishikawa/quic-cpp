#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <sys/_endian.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/types.h> //ソケットタイプ
#include <arpa/inet.h> //バイトオーダの変換に利用
#include <unistd.h> //close()に利用
#include <string>   //string型
#include <time.h>

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

    if( bind( sockfd, ( struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) {
        std::cout<< "Error bind:" << std::strerror( errno );
        exit( 1 );        
    }

    if( listen( sockfd, SOMAXCONN ) < 0 ) {
        std::cout<< "Error listen:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }
    
    struct sockaddr_in get_addr;
    socklen_t len = sizeof( struct sockaddr_in );
    int connect = accept( sockfd, ( struct sockaddr *) &get_addr, &len );

    if( connect < 0 ) {
        std::cout<< "Error sccept:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }

    char recive_str[256];
    if( recv( connect, recive_str, sizeof( recive_str ), 0 ) < 0 ) {
        std::cout<< "Error recv:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }

    std::cout<< recive_str << std::endl;

    char send_str[] = "ServerHello";
    if( send( connect, send_str, sizeof( recive_str ), 0 ) < 0 ) {
        std::cout<< "Error send:" << std::strerror( errno );
        close( sockfd );
        exit( 1 );
    }
    
    close( connect );
    close( sockfd );

    return 0;
}
