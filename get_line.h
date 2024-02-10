/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:22:21 by sel-hasn          #+#    #+#             */
/*   Updated: 2024/01/23 14:22:42 by sel-hasn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_line(int fd);
char	*line(char *s);
char	*rest_of_str(char *s);
char	*read_line(char *s, int fd);
size_t	f_strlen(const char *s);
int		f_newline(char *s);
char	*f_strdup(const char *s);
char	*f_strjoin(char *s1, char *s2);
char	*f_substr(char const *s, unsigned int start, size_t len);

#endif
