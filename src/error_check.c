/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:24:10 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/20 15:35:08 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_usage(char **av)
{
	if (ft_strncmp(av[0], "./pipex_bonus", 14) == 0)
		write(2, "Usage: ./pipex infile cmd1 cmd2 cmd3 ... outfile\n", 50);
	else
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
	exit(EXIT_FAILURE);
}

void	print_error(char *message, char *arg)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
}

void	check_files(char **av)
{
	if (access(av[1], R_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", av[1]);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", av[1]);
	}
	if (access(av[4], W_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", av[4]);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", av[4]);
	}
}

void	check_error(t_pipex *pipex, char **av)
{
	check_files(av);
	if (pipex->cmd1[0] == NULL)
		print_error("command not found: ", "empty");
	if (pipex->cmd2[0] == NULL)
		print_error("command not found: ", "empty");
	if (pipex->path_env == NULL)
		print_error("path not found: ", "path");
	if (pipex->path_cmd1 == NULL)
		print_error("command not found: ", pipex->cmd1[0]);
	if (pipex->path_cmd2 == NULL)
		print_error("command not found: ", pipex->cmd2[0]);
}
