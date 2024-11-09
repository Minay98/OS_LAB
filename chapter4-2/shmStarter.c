#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {

    //Create shared memory
    key_t key = IPC_PRIVATE;
    //int shmget(key_t key, size_t size, int shmflg);

    
    if (shm_id == -1) {
        perror("Failed to create shared memory");
        exit(1);
    }
    // Create childe process
    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    
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
        // Separation of shared memory from process memory space
        //int shmdt(const void *shmaddr);
    } else { 
        //Send message to shared memory

        wait(NULL); 
        //Separation of shared memory from address space
        //int shmdt(const void *shmaddr);

        //Delete shared memory
        //int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    }

    return 0;
}
