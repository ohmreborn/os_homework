#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> // fork
#include <sys/resource.h> // get rusage

void show_mem(){ 
	struct rusage mem_info; 
	getrusage(RUSAGE_SELF, &mem_info); 
	int mem = mem_info.ru_maxrss / (1024 * 1024);
	printf("%d MB\n", mem); 
}

int main(int argc, char *argv[]){ 
	int memsize;
	if (argc > 1) {
		memsize = atoi(argv[1]) * 1024 * 1024; // Convert MB to bytes
	} else {
		memsize = 50 * 1024 * 1024; // default 50 MB
	}
	printf("before allocate memory\n");
	show_mem(); 

	if (memsize % sizeof(int) != 0){
		printf("memsize is doesn't fit in sizeof int\n");
		return 1;
	}
	int num_element = memsize / sizeof(int);
	int *a = (int *)malloc(memsize); 
	if (!a){
		printf("cannot use malloc\n");
		return 1;
	}
	for (int i=0;i< num_element;i++){ 
		a[i] += 1; 
	}

	pid_t child_id = fork();
	if (child_id < 0){
		free(a);
		printf("cannot fork child procress \n");
		return 1;
	}
	if (child_id == 0){ // child procress
		printf("child use before write a memory: ");
		show_mem(); 
		for (int i=0;i<num_element;i++){
			a[i] = 2;
		}
		printf("child use after write a memory: ");
		show_mem(); 
	}else{ // parent procress
		for (int i=0;i<num_element;i++){
			a[i] = 1;
		}
		printf("parent use: ");
		show_mem(); 
		int status;
		wait(&status);
	}

	free(a); 
	return 0; 
}
