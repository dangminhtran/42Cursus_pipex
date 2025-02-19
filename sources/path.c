/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:21:24 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/19 16:36:45 by dangtran         ###   ########.fr       */
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

char	*check_command_in_path(char *cmd, char *path)
{
	char	full_path[1024];

	ft_strlcpy(full_path, path, sizeof(full_path));
	ft_strlcat(full_path, "/", sizeof(full_path));
	ft_strlcat(full_path, cmd, sizeof(full_path));
	if (access(full_path, X_OK) == 0)
		return (ft_strdup(full_path));
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path;
	char	*token;
	char	*path_copy;
	char	*result;

	path = get_path_from_env(env);
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	token = ft_strtok(path_copy, ":");
	while (token)
	{
		result = check_command_in_path(cmd, token);
		if (result)
		{
			free(path_copy);
			return (result);
		}
		token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
