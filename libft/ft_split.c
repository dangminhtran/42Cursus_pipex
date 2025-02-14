/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:53:22 by dangtran          #+#    #+#             */
/*   Updated: 2025/02/12 10:56:40 by dangtran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_count_word(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*dest;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
		len = 0;
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str + start);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	while (len--)
		dest[len] = str[start + len];
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_len;
	char	**strs;

	strs = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!strs || !s)
		return (ft_free(strs, 0));
	i = 0;
	while (*s)
	{
		word_len = 0;
		while (*s == c && *s)
			s++;
		word_len = ft_count_word_len(s, c);
		if (word_len)
		{
			strs[i] = ft_substr(s, 0, word_len);
			if (!strs[i])
				return (ft_free(strs, i));
			i++;
		}
		s += word_len;
	}
	strs[i] = 0;
	return (strs);
}
