/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:23:18 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/02 15:07:51 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_usage(void)
{
	write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 49);
	exit(EXIT_FAILURE);
}

void	print_error(char *message, char *arg, int exit_code, t_pipex *pipex)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	if (arg != NULL)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	free_all(pipex);
	exit(exit_code);
}

void	check_file(t_pipex *pipex, int mode)
{
	if (mode == 0)
	{
		if (access(pipex->name_in, R_OK) == -1)
		{
			perror(pipex->name_in);
			free_all(pipex);
			exit(1);
		}
	}
	else
	{
		if (access(pipex->name_out, W_OK) == -1)
		{
			if (!(errno == ENOENT))
			{
				perror(pipex->name_out);
				free_all(pipex);
				exit(1);
			}
		}
	}
}

void	check_access_cmd(t_pipex *pipex)
{
	if (access(pipex->path_cmd, X_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", pipex->path_cmd, 126, pipex);
		else if (errno == ENOENT)
			print_error("no such file or directory: ",
				pipex->path_cmd, 127, pipex);
	}
}

void	parse_and_check_cmd(t_pipex *pipex, int i)
{
	pipex->cmd = ft_split(pipex->cmds[i], ' ');
	pipex->path_cmd = get_path_cmd(pipex->cmd[0], pipex->path);
	if (pipex->cmd[0] == NULL)
		print_error("command not found: ", "", 127, pipex);
	if (ft_strncmp(pipex->cmd[0], "./", 2) == 0
		|| ft_strchr(pipex->cmd[0], '/') != NULL)
		check_access_cmd(pipex);
	if (access(pipex->path_cmd, F_OK) == -1)
		print_error("command not found: ", pipex->cmd[0], 127, pipex);
}
