#include <iostream>
#include <vector>

#include <sys/types.h>
#include <unistd.h>

/**
 * fork() -- a tranditional way for copying process
 * ParentProcess -- fork() --> ChildProcess
 * fork is used for multi-tasking
 * 
 * reference: https://github.com/angrave/SystemProgramming/wiki/Forking,-Part-2:-Fork,-Exec,-Wait
 */

pid_t child_p;

void CleanUp (int signal);

int main (void) {
    signal (SIGCHLD, CleanUp);
    std::vector<char> args;
    args.push_back('a');
    args.push_back('l');

    child_p = fork();
    std::cout << "PID: " << child_p << std::endl;

    if (child_p == 0) {
        std::cout << "This is child process" << std::endl;

        // general ls call
//        execl ("/bin/ls", "ls", "-al", args, (char*)0);       // This cannot be run
        execl ("/bin/ls", "ls", "-al", (char*)0);

        perror ("fork - exec failed");
    } else if (child_p > 0) {
        std::cout << "This is parent process" << std::endl;
        sleep(4);
        // solution 1
        //wait((int*) 0);
        // solution 2
        //waitpid (child_p, NULL, 0);
    } else {
        std::cout << "fork failed" << std::endl;
        exit (EXIT_FAILURE);
    }

    return 0;
}

void CleanUp (int signal) {
    int status;
    //pid_t == -1 : same as wait(2), wait for arbitrary child process
    //WNOHANG : immediately return even if there is no terminated child process
    while (waitpid ((pid_t) (-1), 0, WNOHANG) > 0) {}
}