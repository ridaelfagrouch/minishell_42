# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by ███████╗██║       #+#    #+#              #
#    Updated: 2022/06/24 16:15:19 by rel-fagr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# --------------------------- Terminal Color Codes --------------------------- #
NC := \033[0m
RED := \033[31;1;3m
YEL := \033[33;1;3m
GRA := \033[37;1;3m
CYN := \033[36;1;3m
GRN := \033[32;1;3m
MGN := \033[35;1;3m
BLU := \033[34;1;3m

# ---------------------------------------------------------------------------- #

define TITLE
${RED}
+ ---------------------------------------------------------------------------- +
|   __   __  __   __    _  ___   _______  __   __  _______  ___      ___       |
|  |  |_|  ||  | |  |  | ||   | |       ||  | |  ||       ||   |    |   |      |
|  |       ||  | |   |_| ||   | |  _____||  |_|  ||    ___||   |    |   |      |
|  |       ||  | |       ||   | | |_____ |       ||   |___ |   |    |   |      |
|  |       ||  | |  _    ||   | |_____  ||       ||    ___||   |___ |   |___   |
|  | ||_|| ||  | | | |   ||   |  _____| ||   _   ||   |___ |       ||       |  |
|  |_|   |_||__| |_|  |__||___| |_______||__| |__||_______||_______||_______|  |
|                                                                              |
+ ---------------------------------------------------------------------------- +
${NNN}${GRA}
                            \t\t\t- Created By ${BLU}SleakyBlinders${NNN}\n
endef
export TITLE

# ---------------------------------------------------------------------------- #
CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror -lreadline -fsanitize=address -static-libsan

NAME		:= minishell
MAIN		:= minishell.c
HEADER		:= minishell.h

LIBFT_ARCH	:= libft/libft.a
LEXR_ARCH	:= srcs/lexer/liblexer.a
PARS_ARCH	:= srcs/parser/libparser.a
EXEC_ARCH	:= srcs/executor/libexecutor.a
ARCHIVES	:= -Llibft -lft \
			-Lsrcs/lexer -llexer \
			-Lsrcs/parser -lparser \
			-Lsrcs/executor -lexecutor

# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re title

all: title ${NAME}

${LIBFT_ARCH}:
	@make -C libft/

${LEXR_ARCH}:
	@make -C srcs/lexer/

${PARS_ARCH}:
	@make -C srcs/parser/

${EXEC_ARCH}:
	@make -C srcs/executor/

${NAME}: ${LIBFT_ARCH} ${LEXR_ARCH} ${PARS_ARCH} ${EXEC_ARCH} ${HEADER}
	@${CC} ${CC_FLAGS} ${MAIN} -o ${NAME} ${ARCHIVES} -g
	@echo "${GRN}Executable ${GRA}${NAME}${GRN} created \
		successfully${NNN} :)\n"

clean:
	@make -C libft/ clean
	@make -C srcs/lexer/ clean
	@make -C srcs/parser/ clean
	@make -C srcs/executor clean

fclean: clean
	@make -C libft/ fclean
	@make -C srcs/lexer/ fclean
	@make -C srcs/parser/ fclean
	@rm -f ${NAME}
	@echo "\n${GRA}${NAME}${RED}\texecutable file has been deleted${NNN}"
	@make -C srcs/executor fclean

re: fclean all

title:
	@clear
	@echo "$$TITLE"

# ---------------------------------------------------------------------------- # 
