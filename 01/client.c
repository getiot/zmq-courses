#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Connecting to server...\n");

    void * context = zmq_ctx_new();
    void * socket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(socket, "tcp://localhost:5555");

    for(int i = 0; i < 10; ++i)
    {
        char buffer[10];
        const char * requestMsg = "Hello";
        int bytes = zmq_send(socket, requestMsg, strlen(requestMsg), 0);
        printf("[Client][%d] Sended Request Message: %d bytes, content == \"%s\"\n", i, bytes, requestMsg);

        bytes = zmq_recv(socket, buffer, 10, 0);
        buffer[bytes] = '\0';
        printf("[Client][%d] Received Reply Message: %d bytes, content == \"%s\"\n", i, bytes, buffer);

    }

    zmq_close(socket);
    zmq_ctx_destroy(context);

    return 0;
}