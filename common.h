#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "services/console_msg.h"
#include "maps/map.h"

#define COMMUNICATION_DOMAIN AF_INET