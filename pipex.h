/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:15:14 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/26 11:35:07 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_line.h"

typedef struct s_envpath
{
	char	**env;
	char	**path;
}	t_envpath;

void	pipex(char **arv, char **env);
void	parentprocess(t_envpath *enp, int *pip);
void	childprocess1(char *oufile, char *cmd2, t_envpath *enp, int *pip);
void	childprocess(char *infile, char *cmd1, t_envpath *enp, int *pip);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dsize);
size_t	ft_strlen(const char *str);
char	*fixcmd(char *command);
void	freepath(char **path);
char	*accesspath(char **path, char *command);
void	printerr(char *cmdname);
char	*checkpath(char **env);
int		ft_cmp(char *s1, char *s2);

void	pipex_bonus(int arc, char **arv, int pip[2][2], t_envpath *enp);
void	firstcmd(char **arv, int *pip, t_envpath *enp);
void	lastcmd(int arc, char **arv, int *pip, t_envpath *enp);
void	middelcmd(int i, char **arv, int pip[2][2], t_envpath *enp);
int		ft_cmp(char *s1, char *s2);
void	checkher_doc(char *delimiter);
void	dup_close(int *pip, int fd);
void	infilerror(int fd);
void	checkmiddel(int arc, char **arv, int pip[2][2], t_envpath *enp);

#endif
