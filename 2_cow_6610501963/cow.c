#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> // fork
#include <sys/wait.h> // wait
#include <sys/resource.h> // get rusage

void show_mem(){ 
	struct rusage mem_info; 
	getrusage(RUSAGE_SELF, &mem_info); 
	// On Linux, ru_maxrss is in kilobytes, not bytes
	int mem = mem_info.ru_maxrss / 1024;  // Convert KB to MB
	printf("%d MB\n", mem); 
}

int main(int argc, char *argv[]){ 
	int memsize;
	if (argc > 1) {
		memsize = atoi(argv[1]) * 1024 * 1024; // Convert MB to bytes
	} else {
		memsize = 50 * 1024 * 1024; // default 50 MB
	}
	printf("before allocate memory: ");
	show_mem(); 

	if (memsize % sizeof(int) != 0){
		printf("memsize doesn't fit in sizeof int\n");
		return 1;
	}
	int num_element = memsize / sizeof(int);
	int *a = (int *)malloc(memsize); 
	if (!a){
		printf("cannot use malloc\n");
		return 1;
	}
	// Initialize the array to ensure pages are allocated
	for (int i=0; i < num_element; i++){ 
		a[i] = 1; 
	}

	printf("after allocate and write memory: ");
	show_mem();

	pid_t child_id = fork();
	if (child_id < 0){
		free(a);
		printf("cannot fork child process\n");
		return 1;
	}
	if (child_id == 0){ // child process
		printf("child use before write a memory: ");
		show_mem(); 

		// Write to the array to trigger COW
		for (int i=0; i < num_element; i++){
			a[i] = 2;
		}

		printf("child use after write a memory: ");
		show_mem(); 
		exit(0);
	} else { // parent process
			 // Write to the array in parent
		for (int i=0; i < num_element; i++){
			a[i] = 3;
		}
		printf("parent use: ");
		show_mem(); 

		int status;
		wait(&status);
		printf("child exit status: %d\n", status);
	}

	free(a); 
	return 0; 
}
