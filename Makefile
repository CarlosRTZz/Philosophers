NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
TFLAGS = -pthread
RM = rm -rf

INC_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS =	main.c			\
		utils.c			\
		free.c			\
		init.c			\
		message.c		\
		monitoring.c	\

OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})

all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D} >/dev/null
	@${CC} ${TFLAGS} ${CFLAGS} -I ${INC_DIR} -c $< -o $@ >/dev/null

${NAME}: ${OBJS}
	@${CC} ${TFLAGS} ${CFLAGS} ${OBJS} -o ${NAME} >/dev/null
	@echo "\033[1;32mCompilation successful: $(NAME)\033[0m"

clean:
	@${RM} ${OBJS_DIR} >/dev/null
	@echo "\033[1;33mObject files deleted.\033[0m"

fclean: clean
	@${RM} ${NAME} >/dev/null
	@echo "\033[1;31m$(NAME) deleted.\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus