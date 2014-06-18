#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

int global_gotsig = 0;

void *gotsig(int sig, siginfo_t *info, void *ucontext) 
{
        global_gotsig++;
        return NULL;
}

void *reader(void *arg)
{
        char buf[32];
        int i;
        int hdlsig = (int)arg;

        struct sigaction sa;
        sa.sa_handler = NULL;
        sa.sa_sigaction = gotsig;
        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);

        if (sigaction(hdlsig, &sa, NULL) < 0) {
                perror("sigaction");
                return (void *)-1;
        }
        i = read(fileno(stdin), buf, 32);
        if (i < 0) {
                perror("read");
        } else {
                printf("Read %d bytes\n", i);
        }
        return (void *)i;
}

main(int argc, char **argv)
{
        pthread_t tid1;
        void *ret;
        int i;
        int sig = SIGUSR1;

        if (argc == 2) sig = atoi(argv[1]);
        printf("Using sig %d\n", sig);

        if (pthread_create(&tid1, NULL, reader, (void *)sig)) {
                perror("pthread_create");
                exit(1);
        }
        sleep(5);
        printf("killing thread\n");
        pthread_kill(tid1, sig);
        i = pthread_join(tid1, &ret);
        if (i < 0)
                perror("pthread_join");
        else
                printf("thread returned %ld\n", (long)ret);
        printf("Got sig? %d\n", global_gotsig);

}

