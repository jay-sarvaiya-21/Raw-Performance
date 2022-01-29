
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include<math.h>
#include<sys/stat.h>

int main(int argc,char *argv[]) {
   int block_size, fd;
   float res;
   size_t  bytes_read, file_size_is=0;
   //unsigned int block_count;
   long start, end;
    //unsigned int *buffer;
   unsigned int result=0;
   struct timeval timecheck;
   unsigned long long size;
   struct stat st;
   stat(argv[1],&st);
   size = st.st_size;
   //printf(" file size is %llu\n",size);
    
    if(argc!=2)
    {
        printf("Enter 2 correct parameters");
    }
    
    
    else if(argc==2){
    
        //262144 //32768 //65536 //16384
        block_size=32768;
        
        fd=open(argv[1],O_RDONLY);
        //unsigned int *buffer=malloc(sizeof(unsigned int)*block_size);
        gettimeofday(&timecheck, NULL);
        start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
        while(1){
            unsigned int *buffer=(unsigned int*)malloc(sizeof(unsigned int)*block_size);
            bytes_read=read (fd,buffer,block_size* sizeof(unsigned int));
            if(fd < 0){
                printf("something went wring whie reading");
                exit(0);
            }
            if(bytes_read)
                file_size_is+=bytes_read;
            else
                break;
            
            for(int j=0;j<bytes_read/4;j++)
            {
                result ^=  buffer[j];
            }
            free(buffer);
        }
        
        gettimeofday(&timecheck, NULL);
        end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
        res=(float)(end - start)/1000;
        close(fd);
        printf("%.3f seconds elapsed\n", res);
        printf("XOR: %08x ",result);
        printf("Performance is =  %f Bytes/s\n", size/res);
        }
    

    
   return 0;
   
} 
       //  struct stat st;
         //stat(argv[1],&st);
         //size = st.st_size;
         //printf(" file size is %llu\n",size);
    //remove block_count to read the entire file && i<= block_count
        /* if (block_size*block_size>size){
        block_count=size/block_size;
             printf("%u", block_count);
             exit(0);
         } */
    
        
         
         //printf("Performance is =  %u", ((block_size*block_count)/(unsigned int)(res*1024*1024)));
     

