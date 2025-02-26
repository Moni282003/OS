#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_request(int client_id) {
    printf("Handling request from Client %d\n", client_id);
    sleep(2);
    printf("Finished processing Client %d\n", client_id);
}

int main() {
    int clients = 5;

    for (int i = 1; i <= clients; i++) {
        if (fork() == 0) {
            handle_request(i);
            exit(0);
        }
    }

    for (int i = 0; i < clients; i++) {
        wait(NULL);
    }

    return 0;
}
