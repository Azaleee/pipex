/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:24:10 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/23 19:19:59 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_usage(void)
{
	write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
	exit(EXIT_FAILURE);
}

void	print_error(char *message, char *arg, int exit_code, t_pipex *pipex)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	if (arg != NULL)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	pipex->exit_code = exit_code;
}

void	check_files(char **av, t_pipex *pipex)
{
	if (access(av[1], R_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", av[1], 0, pipex);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", av[1], 0, pipex);
	}
	if (access(av[4], W_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", av[4], 1, pipex);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", av[4], 1, pipex);
	}
}

void	check_acces(t_pipex *pipex)
{
	if (access(pipex->cmd1[0], X_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", pipex->cmd1[0], 0, pipex);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", pipex->cmd1[0], 0, pipex);
	}
	if (access(pipex->cmd2[0], W_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", pipex->cmd2[0], 126, pipex);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", pipex->cmd2[0], 1, pipex);
	}
}

void	check_error(t_pipex *pipex, char **av)
{
	check_files(av, pipex);
	check_acces(pipex);
	if (pipex->path_cmd1 == NULL)
	{
		if (pipex->cmd1[0] != NULL)
			print_error("command not found: ", pipex->cmd1[0], 0, pipex);
		else
			print_error("command not found: ", "", 0, pipex);
	}
	if (pipex->path_cmd2 == NULL)
	{
		if (pipex->cmd1[0] != NULL)
			print_error("command not found: ", pipex->cmd2[0], 127, pipex);
		else
			print_error("command not found: ", "", 127, pipex);
	}
}
