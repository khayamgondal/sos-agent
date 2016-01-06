#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <uuid/uuid.h>

#include "uthash.h"
#include "common.h"
#include "datatypes.h"
#include "arguments.h"
#include "network.h"

int init_statistics(statistics_t *statistics) {
    struct addrinfo hints, *servinfo;
    int rv;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    
    if ((rv = getaddrinfo(STATISTICS_DEST_ADDR, STATISTICS_PORT, &hints,
                          &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }
    for (statistics->dest = servinfo; statistics->dest != NULL;
         statistics->dest = statistics->dest->ai_next) {
        if ((statistics->sock = socket(statistics->dest->ai_family,
                                      statistics->dest->ai_socktype,
                                      statistics->dest->ai_protocol)) == -1) {
            perror("statistics: socket");
            continue;
        }
        break;
    }
    
    int broadcastEnable = 1;
    int ret = setsockopt(statistics->sock, SOL_SOCKET, SO_BROADCAST,
                         &broadcastEnable, sizeof(broadcastEnable));
    
    if (statistics->dest == NULL) {
        fprintf(stderr, "statistics failed to bind\n");
        exit(1);
    }
    return EXIT_SUCCESS;
}

int send_statistics_message(client_t *client,
                                        statistics_t *statistics, time_t *elapsedtime) {
    //char uuid_msg[200];
    char buffer[500];
    connection_info_t info = getinfo(client);
    uint64_t throughput = info.total_sent_bytes / (uint64_t)elapsedtime;
    //uuid_unparse(client->uuid, uuid_msg);
    
    if (client->transfer_request->type == "CLIENT") {
        snprintf(buffer, 500,
                 "{ \"throughput\" : \"%lu\" }",
                 throughput);
        printf(buffer, 500,
                 "{ \"throughput\" : \"%lu\" }",
                 throughput);
        if ((sendto(statistics->sock, buffer, strlen(buffer), 0,
                    statistics->dest->ai_addr, statistics->dest->ai_addrlen)) < 0) {
            perror("Send statistics message\n");
        }
    }
    return EXIT_SUCCESS;
}