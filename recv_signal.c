/**
 * File: recv_signal.c
 * Modified by: Jan Kowal
 * 
 * Brief summary of program:
 * This program uses sigaction to register a handler for the SIGUSR1 signal.
 * The handler retrieves the sival_int value and prints it.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//signal handler that prints the value of the signal and the process id
void handle_sigusr1(int sig, siginfo_t *siginfo, void *context);

int main() {
    struct sigaction sa;

    // Set up the sigaction structure
    sa.sa_sigaction = handle_sigusr1;
    sa.sa_flags = SA_SIGINFO; // Use SA_SIGINFO to get additional information

    // Register the signal handler for SIGUSR1
    sigaction(SIGUSR1, &sa, NULL);

    // Wait in an infinite loop
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context) {
    printf("Received SIGUSR1 signal with value %d from process %d\n", siginfo->si_value.sival_int, siginfo->si_pid);
}