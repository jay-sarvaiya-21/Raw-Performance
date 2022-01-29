
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

float readthis(fd,block_count,block_size) {

    float res;
    unsigned int x=1;
    long start, end;
    struct timeval timecheck;
    size_t  bytes_read, file_size_is=0;
    float time_taken;
    unsigned int result=0;
    int i;
    int check_flag=0,end_flag=0;
    gettimeofday(&timecheck, NULL);
    start = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
    while(1){
        
        //printf("block count is %u, I is %d\n", block_count,i);
        unsigned int *buffer=(unsigned int*)malloc(sizeof(unsigned int)*block_size);
        bytes_read=read (fd,buffer,block_size* sizeof(unsigned int));
        if(bytes_read<0)
        {
          
          end_flag=1;
          break;
        }
        for(int j=0;j<block_size;j++)
         {  //do nothing
            result ^=  buffer[j];
         }
         if(++block_count==x)
         {
            x=2*x;
            gettimeofday(&timecheck, NULL);
            end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
            res=(float)(end - start)/1000; 
            if(res>5 && res<=15)
            {
                check_flag=1;
                printf("Block count IS %u\n",block_count);
                printf("Time taken is %.3f\n",res);
                printf("Performance is =%u Mib/s \n", ((block_size*block_count)/(unsigned int)(res*1024*1024)));
                break;
            }
         }   
        free(buffer);  }
        if(check_flag==0)
         {
            gettimeofday(&timecheck, NULL);
            end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
            res=(float)(end - start)/1000; 
            printf("BLOCK COUNT IS %u\n",block_count);
            printf("Time taken is %.3f\n",res);
            printf("Performance is =  %u Mib/s\n", ((block_size*block_count)/(unsigned int)(res*1024*1024)));
        
         }
         /*if(end_flag==1)
         {
            gettimeofday(&timecheck, NULL);
            end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
            res=(float)(end - start)/1000; 
            printf("BLOCK COUNT IS %u\n",block_count);
            printf("Time taken is %.3f\n",res);
            printf("Performance is =  %u\n", ((block_size*block_count)/(unsigned int)(res*1024*1024)));
        
         }*/

    //printf("XOR: %08xd ",result);
   return res; }



int main(int argc,char *argv[]) {
   int fd;
   float res;
   size_t  bytes_read, file_size_is=0;
   unsigned int block_count=0,block_size;
   long start, end;
   float time_taken;
   //unsigned int *buffer;
   //unsigned int result=0;
   struct timeval timecheck;
    
    if(argc!=3 ){
        printf(" enter the  3 correct parameteres \n");
        exit(0);
    }

    
    if(argc==3){
        block_size=atoi(argv[2]);
        //block_count=atoi(argv[4]);
        fd=open(argv[1],O_RDONLY);
        if (fd<0)
        {
            printf("Cannot open the file! enter the right filename");
            exit(0);
        }
        time_taken=readthis(fd,block_count,block_size);
    }
    return 0;
}

    
    //unsigned int *buffer=malloc(sizeof(unsigned int)*block_size);
    /*while(1)
    {
        
        time_taken=readthis(fd,block_count,block_size);
        if(time_taken>5){
        printf("%.3f time taken was \n", time_taken);
        exit(0);
        }
        else{
            block_count+=1;
        }

    } */

    
    //remove block_count to read the entire file && i<= block_count
        /*while(1){
        unsigned int *buffer=(unsigned int*)malloc(sizeof(unsigned int)*block_size);
        bytes_read = read(fd,buffer,block_size* sizeof(unsigned int));
        if(fd < 0){
            printf("something went wrong whie reading");
        }
        if(bytes_read)
            file_size_is+=bytes_read;
        //for(int j=0;j<block_size;j++)
         //{
            //result ^=  buffer[j];
         //}
    
        gettimeofday(&timecheck, NULL);
        end = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
        res=(float)(end - start)/1000;
           // printf("%.3f before seconds elapsed \n", res);
        if(5<res && block_count%4==0 ){
        printf("%.6f seconds elapsed \n", res);
        printf("Block count is %u\n",block_count);
            exit(0);}
        else{
            block_count+=1;
            
        }
        free(buffer);
         //printf("XOR: %08xd ",result);
        } */
        
