#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "services/console_msg.h"
#include "services/general.h"
#include "services/clean_stdin.h"

#define COMMUNICATION_DOMAIN AF_INET