#include <zmq.h>
#include <stdio.h>
#include "zmq_helper.h"

int main(void)
{
    void * context = zmq_ctx_new();
    void * socket = zmq_socket(context, ZMQ_SUB);
    zmq_connect(socket, "tcp://localhost:5556");

    char * zipcode = "555";
    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, zipcode, strlen(zipcode));
    zipcode = "666";
    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, zipcode, strlen(zipcode));
    zipcode = "777";
    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, zipcode, strlen(zipcode));

    for(int i = 0; i < 50; ++i)
    {
        char * string = s_recv(socket);
        printf("[Subscriber] Received weather report msg: %s\n", string);
        free(string);
    }

    zmq_close(socket);
    zmq_ctx_destroy(context);
    
    return 0;
}
