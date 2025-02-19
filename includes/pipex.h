/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:49:38 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/19 17:48:37 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <../libft/libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmd;
	char	**env;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}			t_pipex;

// MANAGE
int			init_pipe(t_pipex *pipex);
int			ft_error(char *msg);
void		ft_free(char **str);
char		**ft_split_command(char *cmd);

// PATH
char		*get_path_from_env(char **env);
char		*check_command_in_path(char *cmd, char *path);
char		*find_command_path(char *cmd, char **env);

// PIPEX
void		execute_command(char *cmd, char **env);
void		ft_pipex_child(t_pipex *pipex);
void		ft_pipex_parent(t_pipex *pipex);
void		create_pipes_and_fork(t_pipex *pipex);
void		ft_pipex(t_pipex *pipex);

#endif
