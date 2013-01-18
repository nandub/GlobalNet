/*********************************************
GClient - GlobalNet P2P client
Martin K. Schröder (c) 2012-2013

Free software. Part of the GlobalNet project. 
**********************************************/

#ifndef _GCLIENT_H_
#define _GCLIENT_H_ 

#include <string>
#ifndef WIN32
   #include <unistd.h>
   #include <cstdlib>
   #include <cstring>
   #include <netdb.h>
  
#else
 #include <winsock2.h>
 #include <ws2tcpip.h>
 #include <wspiapi.h>
#endif
	
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <numeric>
#include <fcntl.h>
#include <math.h>
#include "optionparser.h"
#include "vsocket/vsocket.h"

using namespace std;

#define LOG(msg) { cout << "["<<__FILE__<<" line: "<<__LINE__<<"] "<<msg << endl; }
#define ERROR(msg) { cout << "["<<__FILE__<<" line: "<<__LINE__<<"] "<< "[ERROR] "<<msg << endl; }
#define ARRSIZE(arr) (unsigned long)(sizeof(arr)/sizeof(arr[0]))

#define SOCKET_BUF_SIZE 1024

#define SOCK_ERROR(what) { \
		if ( errno != 0 ) {  \
			fputs(strerror(errno),stderr);  \
			fputs("  ",stderr);  \
		}  \
		fputs(what,stderr);  \
		fputc( '\n', stderr); \
}

// maximum simultaneous connections
#define MAX_CONNECTIONS 1024
#define MAX_LINKS 1024
#define MAX_SERVERS 32
#define MAX_SOCKETS 1024


struct Service{
	bool initialized;
	
	// on server side
	VSL::VSOCKET clients[MAX_SOCKETS]; // client sockets
	VSL::VSOCKET links[MAX_LINKS];
	
	// on client side 
	VSL::VSOCKET server_link;  // link through which we can reach the other end
	int local_socket; // socket of the local connections
	vector< pair<int, VSL::VSOCKET> > local_clients;
	map<string, void*> _cache;
	
	// listening socket
	VSL::VSOCKET socket;
	
	int (*listen)(Service &self, const char *host, uint16_t port);
	void (*run)(Service &self);
};

struct Application{
	
};

void SRV_initSOCKS(Service &self);
void SRV_initCONSOLE(Service &self);
VSL::VSOCKET SRV_accept(Service &self);

int tokenize(const string& str,
                      const string& delimiters, vector<string> &tokens);
                      
#endif
