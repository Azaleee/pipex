/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:17:29 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/02 15:17:57 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	write_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		write(1, "pipe ", 6);
		i++;
	}
	write(1, "heredoc> ", 10);
}

void	read_heredoc(t_pipex *pipex, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write_pipe(pipex);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(2,
				"\n zsh: do you wish to see all"
				" 4402 possibilities (2201 lines)?\n", 64);
			break ;
		}
		if (ft_strncmp(line, pipex->eof, ft_strlen(pipex->eof)) == 0
			&& line[ft_strlen(pipex->eof)] == '\n')
			break ;
		if (line != NULL)
			write(fd, line, ft_strlen(line));
		free(line);
	}
	free(pipex);
	free(line);
}

int	open_heredoc(t_pipex *pipex)
{
	int		fd;
	int		status;
	pid_t	pid;

	fd = open(".heredoc_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		read_heredoc(pipex, fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(fd);
	fd = open(".heredoc_temp", O_RDONLY);
	return (fd);
}
