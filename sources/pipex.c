/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:26 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/19 17:32:29 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **env)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = ft_split_command(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		if (cmd_args)
			ft_free(cmd_args);
		exit(0);
	}
	cmd_path = find_command_path(cmd_args[0], env);
	if (!cmd_path)
	{
        write(2, "Error: Failed to execute command\n", 33);
		ft_free(cmd_args);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
	{
		ft_free(cmd_args);
		free(cmd_path);
		exit(126);
	}
}

void	ft_pipex_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	if (pipex->infile_fd == -1)
	{
		close(pipex->pipe_fd[1]);
		ft_error("Error: Failed to open infile\n");
	}
	dup2(pipex->infile_fd, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	if (!pipex->cmd[0] || pipex->cmd[0][0] == '\0')
		exit(0);
	execute_command(pipex->cmd[0], pipex->env);
}

void	ft_pipex_parent(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	if (pipex->outfile_fd == -1)
	{
		close(pipex->pipe_fd[0]);
		ft_error("Error: Failed to open outfile\n");
	}
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	if (!pipex->cmd[1] || pipex->cmd[1][0] == '\0')
		exit(0);
	execute_command(pipex->cmd[1], pipex->env);
}

void	create_pipes_and_fork(t_pipex *pipex)
{
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
}

void	ft_pipex(t_pipex *pipex)
{
	int	status1;
	int	status2;

	pipex->infile_fd = open(pipex->infile, O_RDONLY);
	pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	create_pipes_and_fork(pipex);
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
