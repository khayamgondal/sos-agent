#include <unistd.h>
#include <ctype.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "common.h"
#include "datatypes.h"
#include "tcp_thread.h"
#include "arguments.h"
#include "network.h"
#include "discovery.h"
#include "controller.h"


int get_arguments(options_t *options,  int argc, char **argv) { 

	int opt; 
	memset(options, 0, sizeof(options_t)); 

	while(( opt = getopt(argc, argv, "?p:vdc:b:e:l")) != -1) { 
		switch (opt) { 
			case 'p': 
				printf("Protocol = [%s]\n", optarg); 
				if(!strcmp("sctp", optarg)) { 
					options->protocol = SCTP; 
				}else if(!strcmp("tcp", optarg)) { 
					options->protocol = TCP; 	
				} else { 
					printf("Invalid protocol: (sctp, tcp)\n"); 	
					exit(1); 
				}   		
				break; 
			case 'v':
				printf("Verbose = on\n"); 
				options->verbose = 1; 
				break; 
			case 'c': 
				printf("Number of connections = [%s]\n", optarg); 
				options->num_parallel_sock = atoi(optarg); 
				break; 
			case 'd':
				printf("will print tcpdata\n"); 
				options->data_verbose = 1; 
				break; 
			case 'e':
				sscanf(optarg, "%[^:]:%hi", options->controller.send_ip, 
						&options->controller.port); 			
				printf("connection to endpoint: %s:%d\n", 		
					options->controller.send_ip, options->controller.port); 
				options->nonOF = 1; 
				break; 	
			case 'b':
				options->tcp_bind_ip = calloc(1, sizeof(char) *strlen(optarg) +1); 
				strcpy(options->tcp_bind_ip, optarg); 
				printf("binding tcp %s\n", options->tcp_bind_ip); 
				break; 
			case 'l':
				printf("Logging enabled\n"); 
				options->logging = 1; 
				break; 
			case '?':
				display_usage(); 
				exit(1); 
		}
	} 
	if(check_valid_options(options) == EXIT_SUCCESS) { 
		init_discovery(&options->discovery); 
		init_controller_listener(&options->controller); 
		return init_sockets(options); 
	} 	
	else { 
		exit(1);  
	} 
	return 0; 
}

int check_valid_options(options_t *options) { 
	if(options->num_parallel_sock <= 0) { 
		printf("Number of parallel sockets have to at least be 1!\n"); 
		return EXIT_FAILURE; 
	} else if(options->protocol == 0) { 
		printf("Protocol must be selected!\n");  
		return EXIT_FAILURE; 
	} 
	return EXIT_SUCCESS; 	

}


void display_usage() { 
	printf("Usage: \n"); 
	printf("\t-p Protocol { sctp, tcp }\n"); 
	printf("\t-v Verbose \n"); 
	printf("\t-c # (number of parallel connections\n"); 
	printf("\t-d print tcp data from sockets\n"); 
	printf("\t-b <ip> bind to ip\n" ); 
	printf("\t-e <endpoint> connect to endpoint\n"); 
	printf("\t-l enabled mysql logging\n"); 
} 
