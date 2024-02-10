/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:36:05 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/26 09:51:52 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*fixcmd(char *command)
{
	char	**splitcmd;
	char	*cmd;
	int		i;

	i = 0;
	splitcmd = ft_split(command, ' ');
	if (!splitcmd)
		return (NULL);
	cmd = ft_strjoin("/", splitcmd[0]);
	if (!cmd)
		return (free(splitcmd), NULL);
	while (splitcmd[i])
	{
		free (splitcmd[i]);
		i++;
	}
	free (splitcmd);
	return (cmd);
}

void	freepath(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free (path);
}

char	*accesspath(char **path, char *command)
{
	char	*cmd;
	char	*mypath;
	int		i;

	i = 0;
	if (access(command, X_OK) == 0)
		return (command);
	cmd = fixcmd(command);
	while (path[i])
	{
		mypath = ft_strjoin(path[i], cmd);
		if (!mypath)
			return (free(cmd), NULL);
		if (access(mypath, X_OK) == 0)
		{
			freepath(path);
			return (free(cmd), mypath);
		}
		i++;
		free(mypath);
	}
	printerr(command);
	return (NULL);
}

void	printerr(char *cmdname)
{
	write (2, "error: command not found: ", 27);
	write (2, cmdname, ft_strlen(cmdname));
	write (2, "\n", 1);
	exit(127);
}

char	*checkpath(char **env)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	p = "PATH=";
	while (env[i])
	{
		j = 0;
		if (env[i][j] == p[j])
		{
			while (env[i][j] == p[j])
				j++;
			if (p[j] == '\0')
				return (&env[i][j]);
		}
		i++;
	}
	return (NULL);
}
