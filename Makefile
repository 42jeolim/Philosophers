# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeolim <jeolim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 11:02:14 by jeolim            #+#    #+#              #
#    Updated: 2023/03/12 16:30:39 by jeolim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./src/main.c \
				./src/init.c \
				./src/philo.c \
				./src/additional.c \
				./src/check.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	philo
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra
INCLUDE		=	./src/philo.h
RM			= rm -f

YELLOW=\033[1;33m
NC=\033[0m
GREEN=\033[0;32m
PURPLE=\033[0;35m

all			:	$(NAME)

${NAME} : ${OBJS}
	@$(CC) $(OBJS) $(FLAGS) -o $(NAME)
	@echo "⭐️ ${YELLOW}$(NAME) created ⭐️${NC}"


%.o:%.c ${INCLUDES}
	@${CC} ${FLAGS} -o $@ -c $<
	@echo "${GREEN}$@ created ✅${NC}"

clean		:
		$(RM) ./src/*.o
		@echo "👾 ${PURPLE}only object files deleted  👾${NC}"

fclean		:	clean
		$(RM) $(NAME)
		@echo "👾 ${PURPLE} all files deleted  👾${NC}"

re	:
	make fclean 
	make all

.PHONY	:	all clean fclean re