# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teppei <teppei@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 12:46:40 by teppei            #+#    #+#              #
#    Updated: 2022/01/03 14:19:46 by teppei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PTH1		=	pthread1
PTH2		=	pthread2
MTX1		=	mutex1
NAME		=	$(PTH1) $(PTH2) $(MTX1)
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=thread
SRCS1		=	$(PTH1).c
LIBS		=	-lpthread

all: nanozone $(NAME)

nanozone:
	export MallocNanoZone=0

$(PTH1): $(SRCS1)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OBJS) */*.gch
	rm -rf *.dSYM
fclean: clean
	rm -f $(NAME)
	rm -f libs/*.a

re: fclean all
cl: all clean

.PHONY: all clean fclean re cl nanozone
