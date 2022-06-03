# ---------------------------------------------------------------------------- #
# ---------------------------------------------------------------------------- #
# #                                                                          # #
# #       ███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗     # #
# #       ████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝     # #
# #       ██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗       # #
# #       ██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝       # #
# #       ██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗     # #
# #       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝     # #
# #                                                                          # #
# ---------------------------------------------------------------------------- #
# ---------------------------------------------------------------------------- #

# --------------------------- Terminal Color Codes --------------------------- #
NC := \033[0m
RED := \033[0;31;3m
YEL := \033[0;33;3m
GRA := \033[0;37;3m
CYN := \033[0;36;3m
GRN := \033[0;32;3m
MGN := \033[0;35;3m
BLU := \033[0;34;3m

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
CC_FLAGS	:= -Wall -Wextra -Werror -lreadline

NAME		:= minishell
MAIN		:= minishell.c
HEADER		:= minishell.h

LIBFT_ARCH	:= -Llibft -lft
LEXR_ARCH	:= -Lsrcs/lexer -llexer
PARS_ARCH	:= -Lsrcs/parser -lparser
EXEC_ARCH	:= -Lsrcs/executer -lexecuter
ARCHS		:= ${LEXR_ARCH} ${PARS_ARCH} ${LIBFT_ARCH}
# ${EXEC_ARCH}

# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re title

all: title ${NAME}

deps:
	@make -C libft/
	@make -C srcs/lexer/
	@make -C srcs/parser/

${NAME}: deps ${HEADER}
	@${CC} ${CC_FLAGS} ${MAIN} -o ${NAME} ${ARCHS}
	@echo "${GRN}Executable ${GRA}${NAME}${GRN} created" \
		"successfully${NNN} :)\n"

clean:
	@make -C libft/ clean
	@make -C srcs/lexer/ clean
	@make -C srcs/parser/ clean
#@make -C srcs/executer clean

fclean: clean
	@make -C libft/ fclean
	@make -C srcs/lexer/ fclean
	@make -C srcs/parser/ fclean
	@rm -f ${NAME}
	@echo "\n${GRA}${NAME}${RED}\texecutable file has been deleted${NNN}"
#@make -C srcs/executer fclean

re: fclean all

title:
	@clear
	@echo "$$TITLE"

# ---------------------------------------------------------------------------- # 
