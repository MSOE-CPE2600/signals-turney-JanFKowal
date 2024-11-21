/**
 * File: send_signal.c
 * Modified by: Jan Kowal
 * 
 * Brief summary of program:
 * This program sends SIGUSR1 along with a random integer to the process using sigqueue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    srand(time(NULL)); // Seed the random number generator
    int rand_value = rand(); // Generate a random integer

    printf("Sending SIGUSR1 with value %d to process %d\n", rand_value, pid);

    union sigval value;
    value.sival_int = rand_value;

    // Send the signal with the value
    if (sigqueue(pid, SIGUSR1, value) == -1) {
        perror("sigqueue");
        return 1;
    }

    return 0;
}