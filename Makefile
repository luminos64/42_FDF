NAME	= fdf

CC		= cc

CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g

OBJ_DIR	= objs

SRC_DIR	= srcs

LIB_MLX	= ./lib/MLX42

LIB_FTP	= ./lib/libft

LIBFT	= ${LIB_FTP}/libft.a

HEADER	= -I ${LIB_FTP} -I ${LIB_MLX}/include -I .

LIBS	= ${LIB_MLX}/build/libmlx42.a -ldl -lglfw -pthread -lm

SOURCE	= fdf.c key_hook.c projection.c draw.c gnl.c gnl_utils.c split.c \
			map_utils.c map.c

OBJS	= ${SOURCE:%.c=${OBJ_DIR}/%.o}


all:	${NAME}

${LIBFT}:
	${MAKE} -C ${LIB_FTP}

${NAME}:	${OBJS} ${LIBFT}
	cmake $(LIB_MLX) -B $(LIB_MLX)/build && make -C $(LIB_MLX)/build -j4
	${CC} ${OBJS} ${CFLAGS} ${LIBS} ${LIBFT} ${HEADER} -o ${NAME}
	@echo "\033[0;36mFDF Compiled\n\033[0m"

${OBJS}:	${OBJ_DIR}/%.o:	${SRC_DIR}/%.c Makefile fdf.h
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
	rm -rfv ${OBJ_DIR}
	@rm -rfv $(LIB_MLX)/build
	@${MAKE} -C ${LIB_FTP} clean
	@echo "\033[31mMLX Clean Completed\n\033[0m"

fclean: clean
	rm -rfv ${NAME}
	@${MAKE} -C ${LIB_FTP} fclean
	@echo "\033[31mFDF Clean Completed\n\033[0m"

re:	fclean all

.PHONY:	all clean fclean re
