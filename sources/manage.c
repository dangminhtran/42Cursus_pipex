/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:51:20 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/19 17:06:09 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipe(t_pipex *pipex)
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

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split_command(char *cmd)
{
	char	**args;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	return (args);
}
