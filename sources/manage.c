/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:20 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/15 15:56:51 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// V0
/* int   init_pipe(t_pipex *pipex)
{
    if (!pipex)
        return (1);
    pipex->cmd = NULL;
    pipex->env = NULL;
    pipex->infile = NULL;
    pipex->outfile = NULL;
    pipex->infile_fd = 0;
    pipex->outfile_fd = 0; 
    return (0);
} */

int init_pipe(t_pipex *pipex)
{
    if (!pipex)
        return (1);
    pipex->cmd = NULL;
    pipex->env = NULL;
    pipex->infile = NULL;
    pipex->outfile = NULL;
    pipex->infile_fd = 0;
    pipex->outfile_fd = 0;
    pipex->pipe_fd[0] = 0;
    pipex->pipe_fd[1] = 0;
    pipex->pid1 = 0;
    pipex->pid2 = 0;
    return (0);
}

void ft_free(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void	free_pipe(t_pipex *pipex)
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

char    **ft_split_command(char *cmd)
{
    char    **args;
    
    args = ft_split(cmd, ' ');
    if (!args)
        ft_error("Error: Memory allocation failed\n");
    return (args);
}
