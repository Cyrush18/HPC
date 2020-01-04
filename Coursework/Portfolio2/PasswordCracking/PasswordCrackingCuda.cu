#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/*
 Complie
   nvcc -o PasswordCrackingCuda PasswordCrackingCuda.cu
*/
__device__ int pass(char *password){

   char pass1[]="CY9829";
   char pass2[]="PR5782";
   char pass3[]="DE9811";
   char pass4[]="SH9819";

   char *p1 = password;
   char *p2 = password;
   char *p3 = password;
   char *p4 = password;

   char *pd1 = pass1;
   char *pd2 = pass2;
   char *pd3 = pass3;
   char *pd4 = pass4;

   while(*p1 == *pd1){
    
       if(*p1 == '\0'){
          return 1;
       }
       p1++;
       pd1++;
   }
   
    while(*p2 == *pd2){
    
       if(*p2 == '\0'){
          return 1;
       }
       p2++;
       pd2++;
   }

    while(*p3 == *pd3){
    
       if(*p3 == '\0'){
          return 1;
       }
       p3++;
       pd3++;
   }

    while(*p4 == *pd4){
    
       if(*p4 == '\0'){
          return 1;
       }
       p4++;
       pd4++;
   }
 return 0;
}

__global__ void kernel() {

 
char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  

char number[10] = {'0','1','2','3','4','5','6','7','8','9'};
  

  char password[7];
  password[6] = '\0';
  int c, d, e, f;

     for(c=0;c<10;c++){
      for(d=0; d<10; d++){
       for(e=0; e<10; e++){
        for(f=0; f<10; f++){

        password[0] = alphabet[blockIdx.x];
        password[1] = alphabet[threadIdx.x];
        password[2] = number[c];
        password[3] = number[d];
        password[4] = number[e];
        password[5] = number[f];

        if(pass(password)){
            printf("Password successfully cracked: %s\n", password);
        }

       }
      }
     }
    }
   }

/*
claculating the time difference.
*/
int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
     long long int ds =  finish->tv_sec - start->tv_sec;
     long long int dn =  finish->tv_nsec - start->tv_nsec;

     if(dn < 0 )
     {
      ds--;
      dn += 1000000000;
      }

     *difference = ds * 1000000000 + dn;
    return !(*difference > 0);
}


/*
  Calulating the time
*/
int main(int argc, char *argv[])
{

    struct timespec start, finish;  
    long long int time_elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    kernel <<<26, 26>>>();

    cudaThreadSynchronize();


    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &time_elapsed);
     printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                           (time_elapsed/1.0e9));
  return 0;
}







