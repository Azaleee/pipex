/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:41:15 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/29 01:21:44 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	else
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_pipes(t_pipex *pipex, int **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	else
	{
		while (i < pipex->nb_cmds - 1)
		{
			if (tab[i])
				free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_all(t_pipex *pipex)
{
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	if (pipex->cmd != NULL)
		free_split(pipex->cmd);
	if (pipex->path_cmd != NULL)
		free(pipex->path_cmd);
	if (pipex->pipes)
		free_pipes(pipex, pipex->pipes);
	if (pipex->pid)
		free(pipex->pid);
	if (pipex)
		free(pipex);
}
