#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>
/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code.

  Compile with:
    cc -o Password-With-MultiThread Password-With-MultiThread.c -lcrypt -pthread

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./Password-With-MultiThread > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$1ocIiuN6StvEskjsYoYBid/gy8zXybieNCm9uM94nRw.ik9I04W3DJg0E52dswnozLmM0BIlzRZxgd.TleBwp1",
  "$6$KB$0acBNTGTBysZyAbAv6UxIPgPhuq.AeBkhiAnKqVZTql3xoS/8vSZj4zBjmAF76Pe8yQ1u5UDIzrDwMpqhmbOw1",
  "$6$KB$3KYrSUKBv9/oMeWm/SIy9Amw/ygDkOsBfP5FqWras2fl88rntJK2TmV0hEOVD4P5vPz8.nm31zDCvfy5Vx57Y/"
};

/**
 Required by lack of standard function in C.  
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void Thread(char *paswd) {
  pthread_t thread_1, thread_2;

  void *kernel_function_1();
  void *kernel_function_2();
 
  pthread_create(&thread_1, NULL, kernel_function_1, paswd);
  pthread_create(&thread_2, NULL, kernel_function_2, paswd);

  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
}
/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the
 start of the line. Note that one of the most time consuming operations that
 it performs is the output of intermediate results, so performance experiments
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void *kernel_function_1(char *salt_and_encrypted){
  int a, b, c;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='M'; a++){
    for(b='A'; b<='Z'; b++){
     
      for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a, b,c);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }

    }
  }
  printf("%d solutions explored\n", count);
}
void *kernel_function_2(char *salt_and_encrypted){
  int d, e, f;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(d='N'; d<='Z'; d++){
    for(e='A'; e<='Z'; e++){
     
      for(f=0; f<=99; f++){
        sprintf(plain, "%c%c%02d", d, e,f);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }

    }
  }
  printf("%d solutions explored\n", count);
}


int time_difference(struct timespec *start, struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main(){
  int i;
  struct timespec start, finish;  
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  for(i=0;i<n_passwords;i<i++) {
    Thread(encrypted_passwords[i]);
  }
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));

  return 0;
}
