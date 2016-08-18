#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <string.h>

// writebuf should write the entire contents of buf to a file
// on success 0 should be returned, else an error as returned by write().
int writebuf(int filedescriptor, const char *buf, size_t length)
{
	ssize_t rv = write(filedescriptor, buf, length);  //we can remove the if statement since it does not matter what rv is it will be changed to zero even if rv ends up being zero.	
	rv = 0;
	return rv;
}


int main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)		// if two or three arguements are given then the program accepts it.
		errx(EXIT_FAILURE, "No target file supplied");
	int fd = creat(argv[1], S_IRUSR|S_IWUSR);
	if (fd < 0)
		err(EXIT_FAILURE, "Failed to open target file for writing.");
	char *msg = "Hello world ";
	
	writebuf(fd, msg, strlen(msg));
	
	if(sizeof(argc) > 2)	// if there exist more than two arguments in other words if a second argument is given.
	{
		writebuf(fd,argv[2],strlen(argv[2]));	// write new argument to the same file
	}
	close(fd);
	return 0;
}

