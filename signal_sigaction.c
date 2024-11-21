/**
 * File: signal_sigaction.c
 * Modified by: Jan Kowal
 * 
 * Brief summary of program:
 * This program uses sigaction to register a handler for the SIGUSR1 signal.
 * The handler prints the process identifier of the sender.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//Prints the process ID of the sender
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
    printf("Received SIGUSR1 signal from process %d\n", siginfo->si_pid);
}

/**
 * Command to send SIGUSR1 to the process:
 * kill -SIGUSR1 <PID>
 * Replace <PID> with the actual process ID of the running program.
 */