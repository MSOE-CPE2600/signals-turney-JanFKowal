/**
 * File: signal_alarm.c
 * Modified by: Jan Kowal
 * 
 * Brief summary of program:
 * This program schedules an alarm to be sent after 5 seconds and handles the SIGALRM signal.
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Signal handler for SIGALRM - prints a message
 */
void handle_alarm(int sig);

int main() {
    // Register the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    // Schedule an alarm to be sent after 5 seconds
    alarm(5);

    // Wait until a signal is received
    while(1) {
        printf("Waiting for alarm...\n");
        sleep(1);
    }

    return 0;
}
void handle_alarm(int sig) {
    printf("Received SIGALRM signal\n");
    exit(1);
}