SRCS		=	./src/main.c \
				./src/init.c \
				./src/utils.c \
				./src/philo.c

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