/**
 * Modified by: Jan Kowal
 * 
 * Brief summary of modifications:
 * - Added a signal handler for SIGSEGV to print a message when a segmentation fault occurs.
 ends up going in an infinite loop of printing the message becuase it goes right back to
 trying to access the null pointer
 */

#include <stdio.h>
#include <signal.h>

//Prints a message when a segmentation fault occurs
void handle_sigsegv(int sig);

int main (int argc, char* argv[]) {
    // Register the signal handler for SIGSEGV
    signal(SIGSEGV, handle_sigsegv);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}

void handle_sigsegv(int sig) {
    printf("Received SIGSEGV signal (Segmentation Fault)\n");
}