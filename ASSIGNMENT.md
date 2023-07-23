A. Functional Requirement:
    ● An echo server program
        ○ Can listen to UDP messages on specific IP and port and reply a same message back to the client.

    ● A client program
        ○ Can send a UDP message to your server and display the echo message. (message, IP and port are configurable)
        ○ Support max-retry option. For example, if max-retry = 10, the client will resend message at most 10 times. The interval between
        each retry should follow the exponential backoff algorithm:
            Reference: https://www.baeldung.com/resilience4j-backoff-jitter
                multiplier = 2
                base = 500ms
                max wait_interval = 8s
        ○ Exit program with exit code 0 after the echo message is received
        ○ Exit program with exit code 1 if reach max-retry

B. Non-Functional Requirement:
    ● Use C language
    ● Use POSIX library (reference: https://zh.wikipedia.org/zh-tw/C_POSIX_library)
    ● Upload your project to Github
    ● Explain anything reviewer needs to know in README.md.
    ● Can run in Debian 10 (nice-to-have)
    ● Video demo

C. References

    C.1. Tips For Testing in Debian
    Assume your project folder is /home/user/project (/Users/linzhengkuan/M800_C_test)
    You can easily launch a Debian 10 linux server and mount your project into it at same time by:
    root@your-pc:/> docker run -it -v /home/user/project:/source debian:10
    root@debian:/> cd /source
    root@debian:/source> // here is your project folder, you can compile and run your program now.
    
    Note: If you want to install anything (ex: gcc), please run “apt-get update” first. After that, you can install gcc by “apt-get install gcc”