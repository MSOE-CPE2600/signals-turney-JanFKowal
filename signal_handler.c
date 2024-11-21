/**
 * Modified by: JAN KOWAL
 * 
 * Brief summary of modifications:
 removed the exit(1) from the handle_signal function
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// prints a message when a signal is received
void handle_signal();

int main() {

    // Register for the signal
    signal(SIGINT, handle_signal);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);
    }

    return 0;
}

void handle_signal() {
    printf("Received a signal\n");
}