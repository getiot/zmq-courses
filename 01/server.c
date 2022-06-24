#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main(void)
{
    void * context = zmq_ctx_new();
    void * socket = zmq_socket(context, ZMQ_REP);
    zmq_bind(socket, "tcp://*:5555");

    while(1)
    {
        char buffer[10];
        int bytes = zmq_recv(socket, buffer, 10, 0);
        buffer[bytes] = '\0';
        printf("[Server] Recevied Request Message: %d bytes, content == \"%s\"\n", bytes, buffer);

        sleep(1);

        const char * replyMsg = "World";
        bytes = zmq_send(socket, replyMsg, strlen(replyMsg), 0);
        printf("[Server] Sended Reply Message: %d bytes, content == \"%s\"\n", bytes, replyMsg);
    }

    zmq_close(socket);
    zmq_ctx_destroy(context);

    return 0;
}