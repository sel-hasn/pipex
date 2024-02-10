# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-hasn <sel-hasn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 18:51:47 by sel-hasn          #+#    #+#              #
#    Updated: 2024/01/26 09:54:37 by sel-hasn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = utils.c utils1.c ft_split.c pipex.c

BSRCS = utils.c utils1.c ft_split.c utils2.c get_line_utils.c get_line.c pipex_bonus.c

OBJ = $(SRCS:.c=.o)

BOBJ = $(BSRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc 

RM = rm -f

HDR = pipex.h

all: $(NAME)

bonus: $(BOBJ)
	$(CC) $(FLAGS) $(BOBJ) -o $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	
%.o:%.c $(HDR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
