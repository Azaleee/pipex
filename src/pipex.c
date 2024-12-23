/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:39:04 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/23 18:52:51 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
	pipe_fd[0] -> Read in file
	pipe_fd[1] -> Write in file
*/

void	exec_cmd1(t_pipex *pipex, int pipe_fd[2], char **env)
{
	close(pipe_fd[0]);
	dup2(pipex->fd_in, STDIN_FILENO);
	close(pipex->fd_in);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execve(pipex->path_cmd1, pipex->cmd1, env);
}

void	exec_cmd2(t_pipex *pipex, int pipe_fd[2], char **env)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	dup2(pipex->fd_out, STDOUT_FILENO);
	close(pipex->fd_out);
	execve(pipex->path_cmd2, pipex->cmd2, env);
}

void	wait_childs(t_pipex *pipex, pid_t pid, pid_t pid2)
{
	int	status;

	if (pipex->path_cmd1 != NULL && pipex->fd_in != -1)
		waitpid(pid, &status, 0);
	if (pipex->path_cmd2 != NULL && pipex->fd_out != -1)
		waitpid(pid2, &status, 0);
	if (pipex->exit_code == 1)
	{
		free_all(pipex);
		exit(1);
	}
	else if (pipex->exit_code == 127)
		;
	else
		pipex->exit_code = (status >> 8) & 0xFF;
}

void	exec_all(t_pipex *pipex, char **env)
{
	pid_t	pid;
	pid_t	pid2;
	int		pipe_fd[2];

	pipe(pipe_fd);
	if (pipex->path_cmd1 != NULL && pipex->fd_in != -1)
	{
		pid = fork();
		if (pid == 0)
			exec_cmd1(pipex, pipe_fd, env);
	}
	if (pipex->path_cmd2 != NULL && pipex->fd_out != -1)
	{
		pid2 = fork();
		if (pid2 == 0)
			exec_cmd2(pipex, pipe_fd, env);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (pipex->path_cmd2 != NULL || pipex->path_cmd1 != NULL)
		wait_childs(pipex, pid, pid2);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		exit_code;

	if (ac != 5)
		print_usage();
	else
	{
		pipex = malloc(sizeof(t_pipex));
		if (pipex == NULL)
			return (0);
		parsing_args(pipex, av, env);
		check_error(pipex, av);
		exec_all(pipex, env);
		exit_code = pipex->exit_code;
		free_all(pipex);
		exit(exit_code);
	}
	return (0);
}
