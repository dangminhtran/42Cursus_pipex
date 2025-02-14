/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:49:38 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/14 19:37:28 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct s_pipex
{
    char	**cmd;
    char	**env;
    char	*infile;
    char	*outfile;
    int		infile_fd;
    int		outfile_fd;
    int		pipe_fd[2];
}	t_pipex;


void	ft_error(char *str);
void	ft_free(char **str);
void	ft_pipex(t_pipex *pipex);
void	ft_pipex_child(t_pipex *pipex, int i);
void	ft_pipex_parent(t_pipex *pipex, int i);

#endif

