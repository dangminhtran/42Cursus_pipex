/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:26 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/15 18:51:43 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_from_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path;
	char	*token;
	char	*path_copy;
	char	full_path[1024];

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
			return (ft_strdup(full_path));
		}
		token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/* void	ft_pipex_child(t_pipex *pipex)
{
	char	*cmd_path;
	char	**cmd_args;

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
		exit(127);
	}
	execve(cmd_path, cmd_args, pipex->env);
	ft_free(cmd_args);
	free(cmd_path);
	exit(1);
} */

// TODO - A RELIRE
void    ft_pipex_child(t_pipex *pipex)
{
    char    *cmd_path;
    char    **cmd_args;

    close(pipex->pipe_fd[0]);
    if (pipex->infile_fd == -1)
    {
        close(pipex->pipe_fd[1]);
        exit(1);
    }
    dup2(pipex->infile_fd, STDIN_FILENO);
    dup2(pipex->pipe_fd[1], STDOUT_FILENO);
    close(pipex->pipe_fd[1]);
    close(pipex->infile_fd);
    close(pipex->outfile_fd);
    
    if (!pipex->cmd[0] || pipex->cmd[0][0] == '\0')
        exit(0);
        
    cmd_args = ft_split_command(pipex->cmd[0]);
    if (!cmd_args || !cmd_args[0])
    {
        if (cmd_args)
            ft_free(cmd_args);
        exit(0);
    }
    cmd_path = find_command_path(cmd_args[0], pipex->env);
    if (!cmd_path)
    {
        ft_free(cmd_args);
        exit(127);
    }
    if (execve(cmd_path, cmd_args, pipex->env) == -1)
    {
        ft_free(cmd_args);
        free(cmd_path);
        exit(126);
    }
}

/* void	ft_pipex_parent(t_pipex *pipex)
{
	char	*cmd_path;
	char	**cmd_args;

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
		exit(127);
	}
	execve(cmd_path, cmd_args, pipex->env);
	ft_free(cmd_args);
	free(cmd_path);
    exit(1);
} */

// TODO - A RELIRE
void    ft_pipex_parent(t_pipex *pipex)
{
    char    *cmd_path;
    char    **cmd_args;

    close(pipex->pipe_fd[1]);
    dup2(pipex->pipe_fd[0], STDIN_FILENO);
    if (pipex->outfile_fd == -1)
    {
        close(pipex->pipe_fd[0]);
        exit(1);
    }
    dup2(pipex->outfile_fd, STDOUT_FILENO);
    close(pipex->pipe_fd[0]);
    close(pipex->infile_fd);
    close(pipex->outfile_fd);

    if (!pipex->cmd[1] || pipex->cmd[1][0] == '\0')
        exit(0);

    cmd_args = ft_split_command(pipex->cmd[1]);
    if (!cmd_args || !cmd_args[0])
    {
        if (cmd_args)
            ft_free(cmd_args);
        exit(0);
    }
    cmd_path = find_command_path(cmd_args[0], pipex->env);
    if (!cmd_path)
    {
        ft_free(cmd_args);
        exit(127);
    }
    if (execve(cmd_path, cmd_args, pipex->env) == -1)
    {
        ft_free(cmd_args);
        free(cmd_path);
        exit(126);
    }
}

/* void	ft_pipex(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	if (pipex->infile_fd == -1)
		ft_error("Error: Failed to open input file\n");
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
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
    exit(EXIT_SUCCESS);
}*/

// TODO - A RELIRE
void    ft_pipex(t_pipex *pipex)
{
    int status1, status2;

    pipex->infile_fd = open(pipex->infile, O_RDONLY);
    pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (pipe(pipex->pipe_fd) == -1)
        exit(1);

    pipex->pid1 = fork();
    if (pipex->pid1 == -1)
        exit(1);
    if (pipex->pid1 == 0)
        ft_pipex_child(pipex);

    pipex->pid2 = fork();
    if (pipex->pid2 == -1)
        exit(1);
    if (pipex->pid2 == 0)
        ft_pipex_parent(pipex);

    close(pipex->pipe_fd[0]);
    close(pipex->pipe_fd[1]);
    if (pipex->infile_fd != -1)
        close(pipex->infile_fd);
    if (pipex->outfile_fd != -1)
        close(pipex->outfile_fd);

    waitpid(pipex->pid1, &status1, 0);
    waitpid(pipex->pid2, &status2, 0);

    if (WIFEXITED(status2))
        exit(WEXITSTATUS(status2));
    else if (WIFSIGNALED(status2))
        exit(128 + WTERMSIG(status2));
    exit(1);
}
