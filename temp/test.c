#include "minishell.h"

char	*find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = NULL;
		path = ft_strjoin(paths[i], "/");
		temp = path;
		path = ft_strjoin(path, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free(paths);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	handle_execute(char *argv, char **envp, int n)
{
	int	fd[2];
	pid_t	pid;
	char 	**cmd;

	if (pipe(fd) == -1)
		printf("error\n");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		cmd = ft_split(argv, ' ');
		if (execve(find_path(envp, cmd[0]), cmd, envp) == -1)
			printf("error\n");
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, WNOHANG);
		close(fd[1]);
		if (n == 1)
			dup2(fd[0], STDIN_FILENO);
		else
			dup2(fd[0], STDOUT_FILENO);
		printf("good\n");
	}
	else
		printf("wow\n");
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	**cmd;

	//handle_execute(argv[1], envp, 1);
	//handle_execute(argv[2], envp, 2);
	cmd = ft_split(argv[1], ' ');
	execve(find_path(envp, cmd[0]), cmd, envp);
	cmd = ft_split(argv[2], ' ');
	execve(find_path(envp, cmd[0]), cmd, envp);
	return (0);
}
