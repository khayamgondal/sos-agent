int init_agent(agent_t *agent) ; 
int create_listen_sockets(agent_t *agent)  ; 
int init_poll(agent_t *agent); 
void setnonblocking(int sock); 
client_t *  handle_host_side_connect(agent_t *agent) ; 
void *get_in_addr(struct sockaddr *sa);
client_t * init_new_client(agent_t *agent, uuid_t *uuid ) ; 
int accept_host_side(agent_t *agent, client_t *new_client) ; 
int connect_agent_side(agent_t *agent, client_t *new_client) ; 
int read_host_send_agent(agent_t * agent, event_info_t *event_host, event_info_t *event_agent); 
int read_agent_send_host(agent_t * agent, event_info_t *event); 
int clean_up_connections(client_t *client);      
int send_data_host(agent_t *agent,  event_info_t *event, int remove_fd) ; 
int close_listener_sockets(agent_t *agent); 
int configure_poll(client_t * client); 
int accept_agent_side( agent_t *agent, event_info_t *event_info); 
int connect_host_side(agent_t *agent, client_t *new_client); 
int agent_connected_event(agent_t *agent, event_info_t *event); 
int get_uuid_and_confirm_client(agent_t *agent, int fd) ; 
int clean_up_unconnected_parallel_sockets(agent_t *agent, client_t *client) ; 
int handle_host_connected(agent_t *agent, client_t * client) ;        
