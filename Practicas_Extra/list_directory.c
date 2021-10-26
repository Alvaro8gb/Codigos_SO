
/* Autohor : ALVARO GARCIA BARRAGAN alvaga28@ucm.es*/

#include  <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include  <stdlib.h>
#include <time.h>


 
#define MAX_BUF   256

void show_stat(char  name_file[] ){
    struct stat file_stat;

    int res =  stat( name_file , &file_stat);

    if(res == -1)
        exit(-1);

    printf("\nName : %s", name_file);
    printf("\n----> Number of i-nodo : %ld ",(long)file_stat.st_ino);
    printf("\n----> User ID of owner :  UID : %ld",(long)file_stat.st_uid);
    printf("\n----> Group ID of owner :  GID : %ld",(long)file_stat.st_gid);
    printf("\n----> Size of file : %lld",(long long)file_stat.st_size);
    printf("\n----> Number of blocks : %lld",(long long)file_stat.st_blocks);
    printf("\n----> Number of links : %ld ",(long)file_stat.st_nlink);
    printf("\n----> Time of last access : %s",ctime((long int * )&file_stat.st_atim));
    printf("----> Time of last modification : %s",ctime((long int * )&file_stat.st_mtim)); 
    printf("----> Time of last status change : %s",ctime((long int * )&file_stat.st_ctim));



    printf("\n");
}
/*

struct stat *file_stat_buffer = malloc(sizeof(struct stat ));

    stat( name_file , file_stat_buffer);

 
    printf("\n%ld ",(long)file_stat_buffer->st_ino);

    free(file_stat_buffer);

*/
void main(int argc, char **argv){
   DIR *dirp = NULL;
   struct dirent *dp = NULL;
   char buf[MAX_BUF];
   
 
    if(argc == 1){
        getcwd(buf, MAX_BUF);
        printf("Directorio actual: %s\n", buf);
        dirp = opendir(buf);
    }else{

        dirp = opendir(argv[1]);

        printf("List and show : %s \n ", argv[1]);
    } 

  
    if (dirp == NULL)  {
        fprintf(stderr,"No puedo abrir %s\n", argv[1]);
    } else {
        
        /* lee entrada a entrada */
        while ( (dp = readdir(dirp)) != NULL)
            show_stat(dp->d_name);

        closedir(dirp); 
      
    }

   exit(0);
}
