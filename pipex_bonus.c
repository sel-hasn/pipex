/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:20:20 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/28 13:27:39 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middelcmd(int i, char **arv, int pip[2][2], t_envpath *enp)
{
	char	*cmdpath;
	char	**cmd;

	cmdpath = accesspath(enp->path, arv[i]);
	dup2(pip[0][0], 0);
	dup2(pip[1][1], 1);
	close(pip[0][0]);
	close(pip[0][1]);
	close(pip[1][0]);
	close(pip[1][1]);
	cmd = ft_split(arv[i], ' ');
	if (execve(cmdpath, cmd, enp->env) < 0)
	{
		free(cmdpath);
		exit(1);
	}
}

void	lastcmd(int arc, char **arv, int *pip, t_envpath *enp)
{
	char	*cmdpath;
	int		fd;
	char	**cmd;

	cmdpath = accesspath(enp->path, arv[arc - 2]);
	if (ft_cmp(arv[1], "here_doc"))
		fd = open(arv[arc - 1], O_APPEND | O_CREAT | O_WRONLY, 0777);
	else
		fd = open(arv[arc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
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
	cmd = ft_split(arv[arc - 2], ' ');
	if (execve(cmdpath, cmd, enp->env) < 0)
	{
		free(cmdpath);
		exit(1);
	}
}

void	firstcmd(char **arv, int *pip, t_envpath *enp)
{
	char	*cmdpath;
	char	**cmd;
	int		fd;

	if (ft_cmp(arv[1], "here_doc") == 1)
	{
		fd = open("here_doc.txt", O_RDONLY);
		cmd = ft_split(arv[3], ' ');
		cmdpath = accesspath(enp->path, arv[3]);
	}
	else
	{
		fd = open(arv[1], O_RDONLY);
		infilerror(fd);
		cmd = ft_split(arv[2], ' ');
		cmdpath = accesspath(enp->path, arv[2]);
	}
	dup_close(pip, fd);
	if (execve(cmdpath, cmd, enp->env) < 0)
	{
		free(cmdpath);
		exit(1);
	}
}

void	pipex_bonus(int arc, char **arv, int pip[2][2], t_envpath *enp)
{
	int	id;

	if (access("here_doc.txt", F_OK) == 0)
		unlink("here_doc.txt");
	if (ft_cmp(arv[1], "here_doc") == 1)
		checkher_doc(arv[2]);
	id = fork();
	if (id == 0)
		firstcmd(arv, pip[0], enp);
	else
	{
		checkmiddel(arc, arv, pip, enp);
		id = fork();
		if (id == 0)
			lastcmd(arc, arv, pip[0], enp);
	}
}

int	main(int arc, char **arv, char **env)
{
	t_envpath	*enp;
	int			pip[2][2];

	enp = malloc(sizeof(t_envpath));
	if (arc >= 5)
	{
		enp->env = env;
		enp->path = ft_split(checkpath(env), ':');
		if (pipe(pip[0]) == -1)
			exit(1);
		pipex_bonus(arc, arv, pip, enp);
		close(pip[0][0]);
		close(pip[0][1]);
		close(pip[1][0]);
		close(pip[1][1]);
		while (wait(NULL) != -1)
			;
		freepath(enp->path);
		free(enp);
	}
	else
	{
		write(1, "error: the number of args not correct\n", 39);
		exit(1);
	}
}
