/* Filename: shm_read.c */
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>


#define BUF_SIZE 1024
#define SHM_KEY 0x1234

struct shmseg {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
};

int main(int argc, char *argv[]) {
   int shmid;
   struct shmseg *shmp;
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
   printf("the id of shared memory is %d \n" , shmid);//****prints the id of the shared memory***** 
   if (shmid == -1) {
      perror("Shared memory");
      return 1;
   }
   
   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);
   printf("the address start form %p \n" , &shmp); //***prints the address of the of the shared memory from where the process will start***
   if (shmp == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }
  
   
   /* Transfer blocks of data from shared memory to stdout , the process start from here */ 
   while (shmp->complete != 1) {
      printf("segment contains : \n\"%s\"\n", shmp->buf);
      if (shmp->cnt == -1) {
         perror("read");
         return 1;
      }
      printf("Reading Process: Shared Memory: Read %d bytes\n", shmp->cnt);
      sleep(3);
   }
   printf("Reading Process: Reading Done, Detaching Shared Memory\n");
   if (shmdt(shmp) == -1) {
      perror("shmdt");
      return 1;
   }
   printf("Reading Process: Complete\n");
   return 0;
}
