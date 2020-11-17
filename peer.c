#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<pthread.h>
int lookup_and_connect( const char *host, const char *service );
int sendall(int socket, char * buf, int *len);
void* send_udp(void *u);
int main(int argc, char *argv[]){
  pthread_t thread;
  pthread_create(&thread, NULL, &send_udp, NULL);
  char* ip_registry = argv[1];
  char* command = argv[2];
  char* inquiry_filename = argv[3];
  int s;
  char* tcp_port = "4090";
  char* udp_port = "7800";
  if ((s = lookup_and_connect(ip_registry, tcp_port)) < 0){
    exit(1);
  }
  pthread_join(thread, NULL);
  return 0;
}
void* send_udp(void *u){
  char* msg = "HELLO";
  while(1){
    sleep(5);
  }
  return 0;
}
int lookup_and_connect( const char *host, const char *service ) {
	struct addrinfo hints;
	struct addrinfo *rp, *result;
	int s;

	/* Translate host name into peer's IP address */
	memset( &hints, 0, sizeof( hints ) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	if ( ( s = getaddrinfo(host, service, &hints, &result ) ) != 0 ) {
		fprintf( stderr, "Client Error: getaddrinfo: %s\n", gai_strerror( s ) );
		return -1;
	}

	/* Iterate through the address list and try to connect */
	for ( rp = result; rp != NULL; rp = rp->ai_next ) {
		if ( ( s = socket( rp->ai_family, rp->ai_socktype, rp->ai_protocol ) ) == -1 ) {
			continue;
		}

		if ( connect( s, rp->ai_addr, rp->ai_addrlen ) != -1 ) {
			break;
		}

		close( s );
	}
	if ( rp == NULL ) {
		perror( "Client Error: connect" );
		return -1;
	}
	freeaddrinfo( result );

	return s;
}
int sendall(int socket, char * buf, int *size){
    int totalBytes = 0;
    int bytesRemaining = *size;
    int n;

    while(totalBytes < *size) {
        n = send(socket, buf + totalBytes, bytesRemaining, 0);
        if (n == -1) { break; }
        totalBytes += n;
        bytesRemaining -= n;
    }
    *size = totalBytes;
		if(n == -1){
			return -1;
		}
		else{
			return 0;
		}
}
