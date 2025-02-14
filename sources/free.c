/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:20 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/14 19:10:04 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// function that init t_pipex
void	ft_init(t_pipex *pipex)
{
    pipex->cmd = NULL;
    pipex->env = NULL;
    pipex->infile = NULL;
    pipex->outfile = NULL;
    pipex->infile_fd = 0;
    pipex->outfile_fd = 0;
    pipex->pipe_fd[0] = 0;
    pipex->pipe_fd[1] = 0;
}

// function to free struct t_pipex
void	ft_free(t_pipex *pipex)
{
    if (pipex->cmd)
        ft_free(pipex->cmd);
    if (pipex->env)
        ft_free(pipex->env);
    if (pipex->infile)
        free(pipex->infile);
    if (pipex->outfile)
        free(pipex->outfile);
}