#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	// int	test = open("infile", O_RDONLY);
	// dup2(test, STDIN_FILENO);
	// close(test);
	// execv("/bin/tr", (char *[]){"tr", "a-z", "A-Z", NULL});
	// pid_t	pid;
	// int		pipe_fd[2];

	// (void)ac;
	// (void)av;
	// pipe(pipe_fd);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(pipe_fd[0]);
	// 	dup2(pipe_fd[1], STDOUT_FILENO);
	// 	close(pipe_fd[1]);
	// 	execve("/usr/bin/sort", (char *[]){"sort", "-u", NULL}, env);
	// }
	// else
	// {
	// 	close(pipe_fd[1]);
	// 	dup2(pipe_fd[0], STDIN_FILENO);
	// 	close(pipe_fd[0]);
	// 	execve("/usr/bin/wc", (char *[]){"wc", "-l", NULL}, env);
	// }
	(void)ac;
	(void)av;
	int	i;

	i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	printf("%s\n", env[31]);
    return 0;
}