#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

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

    strcpy(shared_memory, "Hello, Shared Memory!");

    printf("Message from shared memory: %s\n", shared_memory);

    if (shmdt(shared_memory) == -1) {
        perror("Failed to detach from shared memory");
        exit(1);
    }

    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("Failed to remove shared memory");
        exit(1);
    }

    return 0;
}
