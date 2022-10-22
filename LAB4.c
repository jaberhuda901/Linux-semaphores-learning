
// NAME: JABER-UL HUDA


/* 


*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/sem.h>

#include "semun.h"

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void); // sets semaphore to wait as the program is about to enter the critical section
static int semaphore_v(void); // initializes the semaphore using the SETVAL command in a semctl call

static int sem_id;



int main()
{
	sem_id = semget ((key_t) 1234, 1, 0666 | IPC_CREAT);
	set_semvalue();
	pid_t pid = fork();
	
	switch(pid) {
	case -1:
		printf( "fork() Failed");
		exit(0);
	case 0:
		printf ( "Child: It is the child process! \n");
		semaphore_v();
		break;
	default:
		semaphore_p();
		printf ("Parent: It is the parent process!\n");
		del_semvalue();
	}
	
}

// Other Functions needed for the program
// start

static int set_semvalue(void)
{
	union semun sem_union;
	
	sem_union.val = 0;
	if (semctl(sem_id, 0, SETVAL, sem_union) == -1) return(0);
	return(1);
}


static void del_semvalue(void)
{
	union semun sem_union;
	
	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
		fprintf(stderr, "Failed to delete semaphore\n");
}


static int semaphore_p(void)
{
	struct sembuf sem_b;
	
	sem_b.sem_num = 0;
	sem_b.sem_op = -1; /* P() */
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_p failed\n");
		return(0);
	}
	return(1);
}

static int semaphore_v(void)
{
	struct sembuf sem_b;
	
	sem_b.sem_num = 0;
	sem_b.sem_op = 1; /* V() */
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_v failed\n");
		return(0);
	}
	return(1);
}

// end




