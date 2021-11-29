
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int a_global = 10; 

int main() { 

int b_local = 10; 
int* p_local = (int*)malloc(sizeof(int)); 

*p_local = 10; 
int  pid = fork(); 


if(pid!=0) { 
	a_global += 1;
	b_local += 1;
	(*p_local) += 1;
	wait(NULL); 
} 
else {
	sleep(5);
	a_global += 10;
	b_local += 10;
	(*p_local) += 10;
	 
}

printf("%d %d %d %d \n",pid,a_global,b_local,*p_local);
return 0;

}
