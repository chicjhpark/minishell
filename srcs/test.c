#include <stdio.h>
#include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <string.h>
# include <unistd.h>

int	main(void)
{
	if (open("<make", O_RDONLY) < 0)
		printf("%s\n", strerror(errno));
	return (0);
}
