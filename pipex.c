/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:35:49 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/26 11:37:21 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprocess(char *infile, char *cmd1, t_envpath *enp, int *pip)
{
	char	*cmdpath;
	char	**cmd;
	int		fd;

	cmdpath = accesspath(enp->path, cmd1);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		write (2, "no input file\n", 15);
		exit (1);
	}
	dup2(pip[1], 1);
	dup2(fd, 0);
	close(fd);
	close (pip[0]);
	close (pip[1]);
	cmd = ft_split(cmd1, ' ');
	if (execve(cmdpath, cmd, enp->env) < 0)
	{
		free(cmdpath);
		exit(1);
	}
}

void	childprocess1(char *oufile, char *cmd2, t_envpath *enp, int *pip)
{
	char	*cmdpath;
	int		fd;
	char	**cmd;

	cmdpath = accesspath(enp->path, cmd2);
	fd = open(oufile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		write (2, "can't open the file\n", 21);
		exit(1);
	}
	dup2(pip[0], 0);
	dup2(fd, 1);
	close(fd);
	close(pip[1]);
	close(pip[0]);
	cmd = ft_split(cmd2, ' ');
	if (execve(cmdpath, cmd, enp->env) < 0)
	{
		free(cmdpath);
		exit(1);
	}
}

void	parentprocess(t_envpath *enp, int *pip)
{
	close(pip[1]);
	close(pip[0]);
	wait(NULL);
	wait(NULL);
	freepath(enp->path);
	free(enp);
}

void	pipex(char **arv, char **env)
{
	int			pip[2];
	int			id;
	t_envpath	*enp;

	enp = malloc(sizeof(t_envpath));
	enp->env = env;
	enp->path = ft_split(checkpath(env), ':');
	if (pipe(pip) == -1)
		exit(1);
	id = fork();
	if (id == -1)
	{
		write(2, "can't creat child process", 26);
		exit(1);
	}
	if (id == 0)
		childprocess(arv[1], arv[2], enp, pip);
	else
	{
		id = fork();
		if (id == 0)
			childprocess1(arv[4], arv[3], enp, pip);
		else
			parentprocess(enp, pip);
	}
}

int	main(int arc, char **arv, char **env)
{
	if (arc == 5)
		pipex(arv, env);
	else
	{
		write(2, "error: the number of args not correct\n", 39);
		exit(1);
	}
	return (0);
}
