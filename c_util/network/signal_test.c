#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler();

int sigint_count = 3;

int main()
{
	signal(SIGINT, &sigint_handler);
	
	printf("main(): going into infinite loop, sigint_count = %d\n", sigint_count);
	
	while (1){
		printf("main(): sigint_count == %d, pause() ....\n", sigint_count);
		pause();
		printf("main(): return from pause(), sigint_count == %d, pause() ....\n", sigint_count);
	}
	
	return 0;
}

void sigint_handler()
{
	printf("sigint_handler():\n");
	
	if (--sigint_count <=0 ){
		printf("sigint_handler():exit()...\n");
		exit(1);
	}
	printf("sigint_handler():sigint_count == %d\n", sigint_count);
}

/** output:
main(): going into infinite loop, sigint_count = 3
main(): sigint_count == 3, pause() ....
^Csigint_handler():
sigint_handler():sigint_count == 2
main(): return from pause(), sigint_count == 2, pause() ....
main(): sigint_count == 2, pause() ....
^Csigint_handler():
sigint_handler():sigint_count == 1
main(): return from pause(), sigint_count == 1, pause() ....
main(): sigint_count == 1, pause() ....
^Csigint_handler():
sigint_handler():exit()...
*/