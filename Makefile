# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrichard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/29 16:05:39 by lrichard          #+#    #+#              #
#    Updated: 2021/12/15 18:45:42 by lrichard         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCSDIR					= sources

SRCS					= philosophers.c loop.c utils.c

OBJS					= $(addprefix $(SRCSDIR)/, $(SRCS:.c=.o))

HEADERSDIR				= includes

HEADERS					= $(HEADERSDIR)/philosophers.h

$(SRCSDIR)/%.o: 		$(SRCSDIR)/%.c	$(HEADERS)
						$(CC) $(CFLAGS) -I $(HEADERSDIR) -c $< -o $@

NAME					= philo

CFLAGS					= -Wall -Wextra -Werror -O3 -march=native

CC						= gcc

RM						= rm -f

all:					$(NAME)

$(NAME):				$(OBJS) $(HEADERS)
						$(CC) $(CFLAGS) $(OBJS) -I $(HEADERSDIR) -l pthread -o $@

clean:
						$(RM) $(OBJS)

fclean:					clean
						$(RM) $(NAME)

re:						fclean all

.PHONY:					all clean fclean re
