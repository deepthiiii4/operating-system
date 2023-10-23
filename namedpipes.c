#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
   int pipefds[2];
   int returnstatus;
   char writemessages[2][20];
   char readmessage[20];

   returnstatus = pipe(pipefds);
   
   if (returnstatus == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }
   
   printf("Enter Message 1: ");
   scanf("%s", writemessages[0]);
   
   printf("Writing to pipe - Message 1 is %s\n", writemessages[0]);
   write(pipefds[1], writemessages[0], strlen(writemessages[0]) + 1); // Include null terminator in the message

   read(pipefds[0], readmessage, sizeof(readmessage));
   printf("Reading from pipe – Message 1 is %s\n", readmessage);

   printf("Enter Message 2: ");
   scanf("%s", writemessages[1]);

   printf("Writing to pipe - Message 2 is %s\n", writemessages[1]);
   write(pipefds[1], writemessages[1], strlen(writemessages[1]) + 1);

   read(pipefds[0], readmessage, sizeof(readmessage));
   printf("Reading from pipe – Message 2 is %s\n", readmessage);

   return 0;
}
