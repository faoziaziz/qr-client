#ifndef __web_serv_h
#define __web_serv_h

#include<sys/types.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<microhttpd.h>
#include<stdlib.h>

#define PORT            8888
#define POSTBUFFERSIZE  512
#define MAXNAMESIZE     20
#define MAXANSWERSIZE   512

#define GET             0
#define POST            1


static int answer_to_connection(void *cls,
				struct MHD_Connection *connection,
				const char *url,
				const char *method,
				const char *version,
				const char *upload_data,
				size_t *upload_data_size,
				void **con_cls);

int start_server();

#endif
