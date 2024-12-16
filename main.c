#include "get_next_line_bonus.h"
#include <libc.h>

void f(void)
{
	system("leaks a.out");
}

int main()
{
	//atexit(f);

	int fd = open("file.txt", O_RDWR);
	for(int i = 0; i < 7; i++)
	{
		char *line =  get_next_line(fd);
		printf("%s", line);
		free(line);
	}

}