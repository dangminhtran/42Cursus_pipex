/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:26 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/15 15:44:11 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO - A REVOIR LE PATH
char *get_path_from_env(char **env)
{
    int i = 0;

    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            printf("env[i] = %s\n", env[i]);
            printf("PATH = %s\n", env[i] + 5);
            return env[i] + 5;
        }
        i++;
    }
    return NULL;
}

// V0
/* char *find_command_path(char *cmd, char **env)
{
    char *path = get_path_from_env(env);
    char *token;
    char full_path[1024];

    if (!path)
        return NULL;

    // Duplicate path because strtok modifies the string
    char *path_copy = ft_strdup(path);
    if (!path_copy)
        return NULL;

    token = ft_strtok(path_copy, ":");
    while (token)
    {
        printf("cmd = %s\n", cmd);
        {
            free(path_copy);
            return strdup(full_path);
        }
        token = ft_strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
} */

char *find_command_path(char *cmd, char **env)
{
    char *path;
    char *token;
    char *path_copy;
    char full_path[1024];

    path = get_path_from_env(env);
    if (!path)
        return (NULL);

    path_copy = ft_strdup(path);
    if (!path_copy)
        return (NULL);

    token = ft_strtok(path_copy, ":");
    while (token)
    {
        ft_strlcpy(full_path, token, sizeof(full_path));
        ft_strlcat(full_path, "/", sizeof(full_path));
        ft_strlcat(full_path, cmd, sizeof(full_path));
        
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (strdup(full_path));
        }
        token = ft_strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}

/*
char *find_command_path(char *cmd, char **env)
{
    char *path = getenv("PATH");
    char *token;
    char full_path[1024];

    if (!path)
        return NULL;

    token = strtok(path, ":");
    while (token)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
        if (access(full_path, X_OK) == 0) // Check if executable
            return strdup(full_path);
        token = strtok(NULL, ":");
    }
    return NULL; // Command not found
}
*/

// function is called by the child process to execute the command
/* void    ft_pipex_child(t_pipex *pipex, int i)
{
    char *cmd_path = find_command_path(pipex->cmd[i], pipex->env);
    printf("cmd_path = %s\n", cmd_path);
    if (!cmd_path)
        ft_error("Error: Command not found\n");
    
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
    close(pipex->infile_fd);
    close(pipex->outfile_fd);

    execve(cmd_path, pipex->cmd, pipex->env);
    // perror("execve failed");
    ft_error("Error: Failed to execute command\n");
    free(cmd_path);
    exit(EXIT_FAILURE);
} */ 

void    ft_pipex_child(t_pipex *pipex)
{
    char    *cmd_path;
    char    **cmd_args;

    close(pipex->pipe_fd[0]);
    dup2(pipex->infile_fd, STDIN_FILENO);
    dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    close(pipex->pipe_fd[1]);
    close(pipex->infile_fd);
    close(pipex->outfile_fd);

    cmd_args = ft_split_command(pipex->cmd[0]);
    cmd_path = find_command_path(cmd_args[0], pipex->env);
    if (!cmd_path)
    {
        ft_free(cmd_args);
        ft_error("Error: Command 1 not found\n");
    }

    execve(cmd_path, cmd_args, pipex->env);
    ft_free(cmd_args);
    free(cmd_path);
    ft_error("Error: Failed to execute command 1\n");
}

// function is called by the parent process to wait for the child process to finish
/* void    ft_pipex_parent(t_pipex *pipex, int i)
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
} */

void    ft_pipex_parent(t_pipex *pipex)
{
    char    *cmd_path;
    char    **cmd_args;

    close(pipex->pipe_fd[1]);
    dup2(pipex->pipe_fd[0], STDIN_FILENO);
    dup2(pipex->outfile_fd, STDOUT_FILENO);
    close(pipex->pipe_fd[0]);
    close(pipex->infile_fd);
    close(pipex->outfile_fd);

    cmd_args = ft_split_command(pipex->cmd[1]);
    cmd_path = find_command_path(cmd_args[0], pipex->env);
    if (!cmd_path)
    {
        ft_free(cmd_args);
        ft_error("Error: Command 2 not found\n");
    }

    execve(cmd_path, cmd_args, pipex->env);
    ft_free(cmd_args);
    free(cmd_path);
    ft_error("Error: Failed to execute command 2\n");
}

// function to create pipes and fork processes
 /* void    ft_pipex(t_pipex *pipex)
{
    int i;
    int pid;

    i = 0;
    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    if (pipex->infile_fd == -1)
    // TODO - Remplacer par perror
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
} */

void    ft_pipex(t_pipex *pipex)
{
    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    if (pipex->infile_fd == -1)
        ft_error("Error: Failed to open input file\n");

    pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile_fd == -1)
        ft_error("Error: Failed to open output file\n");

    if (pipe(pipex->pipe_fd) == -1)
        ft_error("Error: Failed to create pipe\n");

    pipex->pid1 = fork();
    if (pipex->pid1 == -1)
        ft_error("Error: Failed to fork\n");
    if (pipex->pid1 == 0)
        ft_pipex_child(pipex);

    pipex->pid2 = fork();
    if (pipex->pid2 == -1)
        ft_error("Error: Failed to fork\n");
    if (pipex->pid2 == 0)
        ft_pipex_parent(pipex);

    close(pipex->pipe_fd[0]);
    close(pipex->pipe_fd[1]);
    close(pipex->infile_fd);
    close(pipex->outfile_fd);

    waitpid(pipex->pid1, NULL, 0);
    waitpid(pipex->pid2, NULL, 0);
}
