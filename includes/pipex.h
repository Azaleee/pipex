/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:40:13 by mosmont           #+#    #+#             */
/*   Updated: 2024/12/15 15:07:34 by mosmont          ###   ########.fr       */
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
	char		**cmd1;
	char		**cmd2;
	char		*path_env;
	char		*path_cmd1;
	char		*path_cmd2;
	int			error_file;
}				t_pipex;

void	print_usage(char **av);
int		open_file(char *file, int mode);
void	parsing_args(t_pipex *pipex, char **av, char **env);

void	free_all(t_pipex *pipex);
void	free_split(char **tab);

char	*ft_get_env(char **env);
char	*get_path_command(char *cmd, char *path);

void	check_error(t_pipex *pipex, char **av);

#endif