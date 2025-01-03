/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:15:03 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/02 14:51:44 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	wait_child(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->nb_cmds)
	{
		if (pipex->pid[i] > 0)
			waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			pipex->exit_code = WEXITSTATUS(status);
		i++;
	}
}

void	handle_files(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (pipex->is_heredoc == 0)
			pipex->fd_in = open_file(pipex, pipex->name_in, 0);
		dup2(pipex->fd_in, STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
		close(pipex->fd_in);
	}
	else if (i == pipex->nb_cmds - 1)
	{
		pipex->fd_out = open_file(pipex, pipex->name_out, 1);
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->fd_out, STDOUT_FILENO);
		close(pipex->fd_out);
	}
}

void	execute_cmd(t_pipex *pipex, int i)
{
	int	j;

	if (i == 0 || i == pipex->nb_cmds - 1)
		handle_files(pipex, i);
	else
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < pipex->nb_cmds - 1)
	{
		if (j != i - 1)
			close(pipex->pipes[j][0]);
		if (j != i)
			close(pipex->pipes[j][1]);
		j++;
	}
	parse_and_check_cmd(pipex, i);
	execve(pipex->path_cmd, pipex->cmd, pipex->env);
}

void	execute_all(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_cmds)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
		{
			perror("fork fail");
			free_all(pipex);
			exit(1);
		}
		if (pipex->pid[i] == 0)
			execute_cmd(pipex, i);
	}
	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	wait_child(pipex);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		exit_code;

	if (ac < 5)
		print_usage();
	else
	{
		pipex = malloc(sizeof(t_pipex));
		if (strcmp(av[1], "here_doc") == 0 && ac >= 6)
		{
			pipex->is_heredoc = 1;
			pipex->eof = av[2];
		}
		else
			pipex->is_heredoc = 0;
		init_struct(pipex, ac, av, env);
		init_pipes(pipex);
		execute_all(pipex);
		exit_code = pipex->exit_code;
		free_all(pipex);
		unlink(".heredoc_temp");
		exit(exit_code);
	}
	return (0);
}
