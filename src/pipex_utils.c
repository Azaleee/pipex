/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:13:47 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/20 15:57:35 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(char *file, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, O_RDONLY);
	else if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		return (-1);
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

char	*get_path_command(char *cmd, char *path)
{
	int		i;
	char	**split_path;
	char	*current_path;
	char	*exec;

	i = 0;
	if (path == NULL)
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
	return (NULL);
}

void	parsing_args(t_pipex *pipex, char **av, char **env)
{
	pipex->fd_in = open_file(av[1], 0);
	printf("%d", pipex->fd_in);
	pipex->fd_out = open_file(av[4], 1);
	pipex->cmd1 = ft_split(av[2], ' ');
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!env || !*env)
	{
		write(STDERR_FILENO, "environment is empty\n", 22);
		exit(1);
	}
	pipex->path_env = ft_get_env(env);
	if (access(pipex->cmd1[0], F_OK) == -1)
		pipex->path_cmd1 = get_path_command(pipex->cmd1[0], pipex->path_env);
	else
		pipex->path_cmd1 = ft_strdup(pipex->cmd1[0]);
	if (access(pipex->cmd2[0], F_OK) == -1)
		pipex->path_cmd2 = get_path_command(pipex->cmd2[0], pipex->path_env);
	else
		pipex->path_cmd2 = ft_strdup(pipex->cmd2[0]);
	pipex->error_file = 0;
}
