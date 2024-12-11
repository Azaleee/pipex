/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:24:10 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/11 22:21:10 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_usage(void)
{
	write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
	exit(EXIT_FAILURE);
}

void	print_error(char *message, char *arg, int *exit_code)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	*exit_code = 1;
}

void	check_files(char **av, int *exit_code)
{
	if (access(av[1], R_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", av[1], exit_code);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", av[1], exit_code);
	}
	if (access(av[4], W_OK) == -1)
	{
		if (errno == EACCES)
			print_error("permission denied: ", av[4], exit_code);
		else if (errno == ENOENT)
			print_error("no such file or directory: ", av[4], exit_code);
	}
}

void	check_error(t_pipex *pipex, char **av)
{
	int	exit_code;

	exit_code = 0;
	printf("%s", pipex->path_env);
	if (!pipex->path_env)
		print_error("path not found", "", &exit_code);
	check_files(av, &exit_code);
	if (pipex->cmd1[0] == NULL || pipex->cmd2[0] == NULL)
		print_error("command not found: ", "empty", &exit_code);
	if (pipex->path_env == NULL)
		print_error("path not found: ", "path", &exit_code);
	if (pipex->path_cmd1 == NULL)
		print_error("command not found: ", pipex->cmd1[0], &exit_code);
	if (pipex->path_cmd2 == NULL)
		print_error("command not found: ", pipex->cmd2[0], &exit_code);
	if (exit_code == 1)
	{
		free_all(pipex);
		exit(1);
	}
}
