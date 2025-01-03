/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:40:13 by mosmont           #+#    #+#             */
/*   Updated: 2025/01/02 15:18:19 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

# include "../libft/libft.h"

typedef struct s_pipex
{
	int			fd_in;
	int			fd_out;
	int			nb_cmds;
	int			exit_code;
	int			is_heredoc;
	pid_t		*pid;
	int			**pipes;
	char		*eof;
	char		*name_in;
	char		*name_out;
	char		*path;
	char		**cmds;
	char		**cmd;
	char		*path_cmd;
	char		**env;
}				t_pipex;

char	*ft_get_env(char **env);
int		open_file(t_pipex *pipex, char *file, int mode);
char	*get_path_cmd(char *cmd, char *path);

void	init_pipes(t_pipex *pipex);
void	init_struct(t_pipex *pipex, int ac, char **av, char **env);

void	print_usage(void);
void	check_file(t_pipex *pipex, int mode);
void	parse_and_check_cmd(t_pipex *pipex, int i);

void	free_split(char **tab);
void	free_all(t_pipex *pipex);

int		open_heredoc(t_pipex *pipex);

#endif