#ifndef NAME_SERVER_H
#define NAME_SERVER_H

#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <fcntl.h> 

#define name_path "name.txt"

char* get_ip();

#endif
