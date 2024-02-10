/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:36:12 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/23 14:45:47 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[start + i] != '\0' && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	wordcount(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
	}
	return (count);
}

static char	**freeword(char **str, size_t idx)
{
	while (idx > 0)
	{
		free(str[idx - 1]);
		idx--;
	}
	free(str);
	return (NULL);
}

static char	**mysplit(char **wd, char const *st, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (st[j] && i < wordcount(st, c))
	{
		while (st[j] == c)
			j++;
		len = 0;
		while (st[j + len] != '\0' && st[j + len] != c)
			len++;
		wd[i] = ft_substr(st, j, len);
		if (!wd[i])
			return (freeword(wd, i));
		j = j + len;
		i++;
	}
	wd[i] = NULL;
	return (wd);
}

char	**ft_split(char const *s, char c)
{
	char	**word;

	if (!s)
		return (NULL);
	word = (char **)malloc (sizeof(char *) * (wordcount(s, c) + 1));
	if (!word)
		return (NULL);
	return (mysplit(word, s, c));
}
