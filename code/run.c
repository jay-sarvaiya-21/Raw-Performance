
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
    int fd,fd_w;
    unsigned int block_size,block_count;
    float res;
    size_t  bytes_read, file_size_is=0;
    long start, end;
    //unsigned int *buffer;
    unsigned int result=0;
    struct timeval timecheck;
    unsigned long long size;
    if(argc!=5 ){
        printf("Please enter the 5 correct parameters\n");
        exit(0);

    }
    block_size=atoi(argv[3]);
    block_count=atoi(argv[4]);
    
    
    if(argc==5){
        if( !strcmp("-r",argv[2]))
        {
            printf("Parameteres for %s i.e for reading are correct \n",argv[2]);
            fd=open(argv[1],O_RDONLY);
            if(fd < 0){
                printf("something went wring whie reading");
                exit(0);
               }
            struct stat st;
            stat(argv[1],&st);
            size = st.st_size;
            gettimeofday(&timecheck, NULL);
            start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
        
            //printf(" file size is %llu\n",size);
            //remove block_count to read the entire file && i<= block_count
            //if (block_size*block_size>size){
            //block_count=size/block_size;
                //printf("%u", block_count);
                //printf("exceeds");
                //block_size=size/block_size;
                //printf(" block size is %u\n", block_size);
                //break;
            // }
            for(int i=0; i<block_count  ;i++){
                unsigned int *buffer=(unsigned int*)malloc(sizeof(unsigned int)*block_size);
                bytes_read=read (fd,buffer,block_size* sizeof(unsigned int));
                if(bytes_read)
                    file_size_is+=bytes_read;
                else
                    break;
                for(int j=0;j<block_size;j++)
                {
                    result ^=  buffer[j];
                }
                free(buffer);
            }
            close(fd);     
            gettimeofday(&timecheck, NULL);
            end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
            res=(float)(end - start)/1000;
            //printf("XOR: %08x\n ",result);
            printf("%.3f seconds passed to sucessfully read the file\n", res);
            //printf("bytes read are %zu\n",file_size_is);
        }
    
        else if( !strcmp("-w",argv[2]))
        {
            printf("Parameteres for %s i.e writing to the file are correct \n",argv[2]);


            for(int i=0; i<block_count  ;i++){
                unsigned int* buffer=(unsigned int*)malloc(sizeof(unsigned int)*block_size);
                for(int j=0;j<block_size;j++)
                {
                    buffer[j] = buffer[j - 1] * 1 + 10;
                    //printf(" %u\n", buffer[j]);
                }
                fd_w=open(argv[1], O_WRONLY | O_CREAT | O_APPEND,0644);
                if(fd_w <0){
                    printf("CANNOT open the file for writing");
                    exit(0);}
                write(fd_w, buffer, block_size);
                close(fd_w);
                free(buffer);
            } 
            printf("succesfully written to the file\n");
            //printf("% u", buffer)
                
        }
        else{
            printf("enter the correcrt parameters");
        }
}
else{
    printf("enter correct parameters");
}
return 0;
}
