/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:39:21 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/14 22:47:15 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char *ft_strtok(char *str, const char *delim)
{
    static char *next = NULL;
    if (str)
        next = str;
    
    if (!next)
        return NULL;

    // Skip initial delimiters
    while (*next && strchr(delim, *next))
        next++;

    if (!*next)
        return NULL;

    char *token = next;

    // Find end of token
    while (*next && !strchr(delim, *next))
        next++;

    if (*next) {
        *next = '\0';
        next++;
    } else {
        next = NULL;
    }

    return token;
}

int	ft_strncmp(char *str1, char *str2, size_t count)
{
	size_t	i;

	if (count == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && i < count - 1)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

