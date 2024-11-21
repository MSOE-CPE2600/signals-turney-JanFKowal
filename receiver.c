/**
 * File: receiver.c
 * Created by: Jan Kowal
 * 
 * Brief summary of program:
 * This program installs a signal handler for the "ball" signal, waits for a random amount of time between 1 and 2 seconds,
 * and sends the signal back to the sender. It also prints status messages and plays the system bell.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX_VOLLEYS 10

int volley_count = 0;
pid_t sender_pid;

void handle_ball(int sig, siginfo_t *siginfo, void *context);

int main() {
    srand(time(NULL)); // Seed the random number generator

    struct sigaction sa;
    sa.sa_sigaction = handle_ball;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Receiver process started with PID %d\n", getpid());

    // Wait in an infinite loop
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}

void handle_ball(int sig, siginfo_t *siginfo, void *context) {
    sender_pid = siginfo->si_pid;
    volley_count = siginfo->si_value.sival_int;

    printf("Received ball from process %d (volley count: %d)\n", sender_pid, volley_count);
    printf("\007"); // Play system bell

    // Wait for a random amount of time between 1 and 2 seconds
    sleep(1 + rand() % 2);

    // Send the ball back
    union sigval value;
    value.sival_int = volley_count + 1;
    sigqueue(sender_pid, SIGUSR1, value);

    printf("Sent ball back to process %d (volley count: %d)\n", sender_pid, volley_count + 1);
    printf("\007"); // Play system bell

    if (volley_count >= MAX_VOLLEYS-1) {
        printf("Game over! Total volleys: %d\n", volley_count+1);
        exit(0);
    }
}