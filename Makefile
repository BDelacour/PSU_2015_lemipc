##
## Makefile for M in /home/delaco_c/rendu/PSU_2015_lemipc
## 
## Made by Delacour Benjamin
## Login   <delaco_c@epitech.net>
## 
## Started on  Mon Mar 14 17:50:47 2016 Delacour Benjamin
## Last update Fri Mar 25 16:39:18 2016 Delacour Benjamin
##

NAME	=	lemipc

CC	=	gcc

RM	=	rm -f

LDFLAGS	=	-lm

CFLAGS	+=	-Wall -Werror -Wextra

SRCS	=	main.c		\
		player.c	\
		screen_map.c	\
		sem_tools.c	\
		move_player.c	\
		IA.c		\
		init.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
