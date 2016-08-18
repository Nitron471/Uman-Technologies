#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
//This program checks the value in test.c and compares it with the first word only in testString.txt
int main(int argc,char **argv)
{
   // int status = system("./test2");

  int program = 1;
  int file = 2;
  if(strcmp(argv[1],"-p") == 0 && strcmp(argv[3],"-t") == 0)	// check if -p and -t are added
  {
 	program = program + 1;
	file = file + 2;
  }
  else if(strcmp(argv[1],"-p") == 0)		//check if only -p is added
  {
	program = program + 1;
	file = file + 1;
	if(strcmp(argv[2],"-t")== 0)	//check if textfile is given
	{
		FILE *fp2;
   		char buff[255];		//attempts to read a.out but gives error

   		fp2 = fopen("./a.out", "r");
  		fscanf(fp2, "%s", buff);
   		printf("%s\n", buff );
   		fclose(fp2);
		return 0;
	}
  }
  else if(strcmp(argv[2],"-t") == 0)		//check if only -t is added
  {
  	file = file + 1;
	if(strcmp(argv[1],"-p")== 0)		//check if program is given
	{
		FILE *fp2;
   		char buff[255];		//attempt to read refdata but gives error

   		fp2 = fopen("refdata", "r");
  		fscanf(fp2, "%s", buff);
   		printf("%s\n", buff );
   		fclose(fp2);
		return 0;
	}
  }

  FILE *fp;
  char path[255]; //reading the program and put contents into file then work with string

  /* Open the command for reading. */
  fp = popen(argv[program], "r"); //type ./ in the command line before mentioning the file name
  if (fp == NULL) {

    exit(1);
  }

  /* Read the output a line at a time - output it. */
  fgets(path, sizeof(path)-1, fp);



  /* close */
  pclose(fp);


  FILE *fp2;
   char buff[255];	//reading the textfile

   fp2 = fopen(argv[file], "r");
   fscanf(fp2, "%s", buff);

   fclose(fp2);

   if(strcmp(path,buff) != 0)		// checks if two strings are the same
	{
		fprintf(stderr,"No match\n");
	}

    return 0;
}


