/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:59:56 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/14 19:12:18 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
    t_pipex pipex;

    if (argc != 5)
        ft_error("Error: Invalid number of arguments\n");
    if (!ft_init(&pipex))
        ft_error("Error: Failed to initialize struct\n");
    pipex.cmd = &argv[2];
    pipex.env = env;
    pipex.infile = argv[1];
    pipex.outfile = argv[4];
    ft_pipex(&pipex);
    return (0);
}