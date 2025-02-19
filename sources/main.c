/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:59:56 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/19 17:16:46 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write(2, "Error: Invalid number of arguments\n", 33);
		return (1);
	}
	if (init_pipe(&pipex) != 0)
	{
		ft_error("Error: Failed to initialize struct\n");
		return (1);
	}
	pipex.cmd = &argv[2];
	pipex.env = env;
	pipex.infile = argv[1];
	pipex.outfile = argv[4];
	ft_pipex(&pipex);
	return (1);
}
