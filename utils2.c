/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:50:23 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/26 11:15:15 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infilerror(int fd)
{
	if (fd == -1)
	{
		write (2, "no input file\n", 15);
		exit (1);
	}
}

int	ft_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

void	checkher_doc(char *delimiter)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("here_doc.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
		exit (1);
	str = get_line(0);
	delimiter = ft_strjoin(delimiter, "\n");
	while (str)
	{
		i = ft_cmp(delimiter, str);
		if (i == 1)
			break ;
		write(2, &i, 1);
		write (fd, str, ft_strlen(str));
		free(str);
		str = get_line(0);
	}
	free(delimiter);
	free(str);
	close(fd);
}

void	checkmiddel(int arc, char **arv, int pip[2][2], t_envpath *enp)
{
	int	id;
	int	i;

	if (ft_cmp(arv[1], "here_doc") == 1)
		i = 4;
	else
		i = 3;
	while (i < (arc - 3))
	{
		pipe(pip[1]);
		id = fork();
		if (id == 0)
			middelcmd(i, arv, pip, enp);
		dup2(pip[1][0], pip[0][0]);
		close(pip[1][0]);
		close(pip[1][1]);
		i++;
	}
}

void	dup_close(int *pip, int fd)
{
	dup2(pip[1], 1);
	dup2(fd, 0);
	close(fd);
	close (pip[0]);
	close (pip[1]);
}
