/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:26 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/14 19:11:32 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// function is called by the child process to execute the command
void    ft_pipex_child(t_pipex *pipex, int i)
{
    if (i == 0)
    {
        dup2(pipex->infile_fd, STDIN_FILENO);
        dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    }
    else if (pipex->cmd[i + 1] == NULL)
    {
        dup2(pipex->pipe_fd[0], STDIN_FILENO);
        dup2(pipex->outfile_fd, STDOUT_FILENO);
    }
    else
    {
        dup2(pipex->pipe_fd[0], STDIN_FILENO);
        dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    }
    close(pipex->pipe_fd[0]);
    close(pipex->pipe_fd[1]);
    execve(pipex->cmd[i], pipex->cmd, pipex->env);
    ft_error("Error: Failed to execute command\n");
}

// function is called by the parent process to wait for the child process to finish
void    ft_pipex_parent(t_pipex *pipex, int i)
{
    if (i == 0)
        close(pipex->pipe_fd[1]);
    else if (pipex->cmd[i + 1] == NULL)
        close(pipex->pipe_fd[0]);
    else
    {
        close(pipex->pipe_fd[0]);
        close(pipex->pipe_fd[1]);
    }
    wait(NULL);
}

// function is called by the main function to create pipes and fork processes
void    ft_pipex(t_pipex *pipex)
{
    int i;
    int pid;

    i = 0;
    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    if (pipex->infile_fd == -1)
        ft_error("Error: Failed to open input file\n");
    pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile_fd == -1)
        ft_error("Error: Failed to open output file\n");
    while (pipex->cmd[i])
    {
        if (pipe(pipex->pipe_fd) == -1)
            ft_error("Error: Failed to create pipe\n");
        pid = fork();
        if (pid == -1)
            ft_error("Error: Failed to fork\n");
        if (pid == 0)
            ft_pipex_child(pipex, i);
        else
            ft_pipex_parent(pipex, i);
        i++;
    }
    close(pipex->infile_fd);
    close(pipex->outfile_fd);
}