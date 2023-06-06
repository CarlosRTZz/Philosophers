NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
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
		routine.c		\

OBJS = $(addprefix ${OBJS_DIR}/, ${SRCS:%.c=%.o})

all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	@${CC} ${TFLAGS} ${CFLAGS} -I ${INC_DIR} -c $< -o $@

${NAME}: ${OBJS}
	@${CC} ${TFLAGS} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "\033[1;32mCompilation successful: $(NAME)\033[0m"

clean:
	@${RM} ${OBJS_DIR}
	@echo "\033[1;33mObject files deleted.\033[0m"

fclean: clean
	@${RM} ${NAME}
	@echo "\033[1;31m$(NAME) deleted.\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus