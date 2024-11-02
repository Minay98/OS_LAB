#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    key_t key = IPC_PRIVATE;
    int shm_id = shmget(key, 1024, IPC_CREAT | S_IRUSR | S_IWUSR);
    if (shm_id == -1) {
        perror("Failed to create shared memory");
        exit(1);
    }

    char *shared_memory = (char *)shmat(shm_id, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("Failed to attach to shared memory");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to fork process");
        exit(1);
    } else if (pid == 0) { 
        sleep(1); 
        printf("Child reads from shared memory: %s\n", shared_memory);
        shmdt(shared_memory); 
    } else { 
        strcpy(shared_memory, "Hello from parent!"); 
        wait(NULL); 
        shmdt(shared_memory); 
        shmctl(shm_id, IPC_RMID, NULL); 
    }

    return 0;
}
