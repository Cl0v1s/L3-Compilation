#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	int p[2];
	pipe(p);
	if(fork() != 0) {
		close(p[1]);
		dup2(p[0],0);
		execlp("./comp_c3a","./comp_c3a",NULL);
		exit(0);
	} else {
		dup2(p[1],1);
		close(p[0]);
		execlp("./comp_imp","./comp_imp",NULL);
		exit(0);
	}
	return EXIT_SUCCESS;

}