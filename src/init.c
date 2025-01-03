/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:41:01 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/29 04:08:01 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipes = malloc(sizeof(int *) * (pipex->nb_cmds - 1));
	if (!pipex->pipes)
		exit(EXIT_FAILURE);
	while (i < pipex->nb_cmds - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipes[i]) == -1)
		{
			printf("%d", i);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_struct(t_pipex *pipex, int ac, char **av, char **env)
{
	pipex->env = env;
	pipex->path = ft_get_env(pipex->env);
	if (pipex->is_heredoc == 0)
	{
		pipex->cmds = &av[2];
		pipex->nb_cmds = ac - 3;
		pipex->fd_in = -1;
	}
	else
	{
		pipex->cmds = &av[3];
		pipex->nb_cmds = ac - 4;
		pipex->fd_in = open_heredoc(pipex);
	}
	pipex->name_in = av[1];
	pipex->name_out = av[ac - 1];
	pipex->fd_out = -1;
	pipex->cmd = NULL;
	pipex->path_cmd = NULL;
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->nb_cmds);
	pipex->exit_code = 0;
	if (pipex->is_heredoc != 1)
		pipex->is_heredoc = 0;
}
