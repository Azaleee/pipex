/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:25:36 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/29 04:19:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(t_pipex *pipex, char *file, int mode)
{
	int	fd;

	if (mode == 0 && pipex->is_heredoc == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
	{
		if (pipex->is_heredoc == 0)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
		return (-1);
	if (fd == -1)
	{
		perror(file);
		free_all(pipex);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char	*ft_get_env(char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			while (env[i][j] != '\0')
				j++;
			break ;
		}
		i++;
	}
	if (j == 0)
		return (NULL);
	return (env[i] + 5 + 1);
}

char	*get_path_cmd(char *cmd, char *path)
{
	int		i;
	char	**split_path;
	char	*current_path;
	char	*exec;

	i = 0;
	if (path == NULL || cmd == NULL)
		return (NULL);
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		current_path = ft_strjoin(split_path[i], "/");
		exec = ft_strjoin(current_path, cmd);
		if (access(exec, X_OK | F_OK) == 0)
		{
			free(current_path);
			free_split(split_path);
			return (exec);
		}
		free(current_path);
		free(exec);
		i++;
	}
	free_split(split_path);
	return (ft_strdup(cmd));
}
