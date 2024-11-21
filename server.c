/**
 * File: server.c
 * Created by: Jan Kowal
 * 
 * Brief summary of program:
 * This program installs a signal handler for the "ball" signal, waits for a random amount of time between 1 and 2 seconds,
 * and sends the signal back to the sender. It also prints status messages and plays the system bell. After setting up the
 * signal handler, it serves the ball to the receiver.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_VOLLEYS 10

int volley_count = 0;
pid_t receiver_pid;

void handle_ball(int sig, siginfo_t *siginfo, void *context);

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    // Get the receiver's process ID by converting the argument to an integer
    receiver_pid = atoi(argv[1]);
    srand(time(NULL)); // Seed the random number generator


    struct sigaction sa;
    sa.sa_sigaction = handle_ball;
    // Use SA_SIGINFO to get additional information
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Server process started with PID %d\n", getpid());

    // Serve the ball to the receiver
    union sigval value;
    value.sival_int = 1;
    sigqueue(receiver_pid, SIGUSR1, value);

    printf("Served ball to process %d (volley count: 1)\n", receiver_pid);
    printf("\007"); // Play system bell

    // Wait in an infinite loop
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

void handle_ball(int sig, siginfo_t *siginfo, void *context) {
    receiver_pid = siginfo->si_pid;
    volley_count = siginfo->si_value.sival_int;

    printf("Received ball from process %d (volley count: %d)\n", receiver_pid, volley_count);
    printf("\007"); // Play system bell

    if (volley_count >= MAX_VOLLEYS) {
        printf("Game over! Total volleys: %d\n", volley_count);
        exit(0);
    }

    // Wait for a random amount of time between 1 and 2 seconds
    sleep(1 + rand() % 2);

    // Send the ball back
    union sigval value;
    value.sival_int = volley_count + 1;
    sigqueue(receiver_pid, SIGUSR1, value);

    printf("Sent ball back to process %d (volley count: %d)\n", receiver_pid, volley_count + 1);
    printf("\007"); // Play system bell
}