/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:52:00 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/12 17:13:07 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (tab[0] == NULL)
		free(tab);
	else
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_all(t_pipex *pipex)
{
	if (pipex->fd_in >= 0)
		close(pipex->fd_in);
	if (pipex->fd_out >= 0)
		close(pipex->fd_out);
	free_split(pipex->cmd1);
	free_split(pipex->cmd2);
	free(pipex->path_env);
	free(pipex->path_cmd1);
	free(pipex->path_cmd2);
	free(pipex);
}
