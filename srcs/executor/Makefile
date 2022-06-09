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
NNN := \033[0m
RED := \033[31;1;3m
YEL := \033[33;1;3m
GRA := \033[37;1;3m
CYN := \033[36;1;3m
GRN := \033[32;1;3m
MGN := \033[35;1;3m
BLU := \033[34;1;3m

# ---------------------------------------------------------------------------- #
CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror

SRCS_DIR	:= srcs/
SRCS_LST	:= env_conversion.c builtin_cmds.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_LST}}

OBJS_DIR	:= objs/
OBJS_LST	:= ${patsubst %.c, %.o, ${SRCS_LST}}
OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS_LST}}

PROJECT 	:= executor
HEADER		:= executor.h
NAME		:= libexecutor.a

MAIN		:= test_main.c

# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re title test_clean test_compile

all: title ${NAME}

title:
	@echo "\n${YEL}\033[4mEntering ${GRA}${PROJECT}${YEL}'s makefile${NNN}\n"

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADER}
	@ar -rcs ${NAME} ${OBJS}
	@echo "$(BLU)Archive file $(GRA)$(NAME)$(BLU) created successfully$(NNN)\n"

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${HEADER}
	@${CC} ${CC_FLAGS} -c $< -o $@
	@echo "${MGN}Object file ${GRA}$@${MGN} created from ${GRA}$<${MGN}${NNN}"

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

test_compile: ${TEST_MAIN} ${HEADER}
	@make -C ../../libft
	@${CC} -Wall -Wextra ${MAIN} -fsanitize=leak -o test_output ${SRCS} -L../../libft -lft
	@echo "${GRN}Testing executable ${GRA}test_output${GRN} created" \
		"successfully${NNN} :)\n"

test_clean: test_output
	@rm -f test_output
	@echo "${GRA}test_output${RED}\texecutable have been deleted${NNN}"

clean:
	@rm -rf ${OBJS_DIR}
	@echo "${GRA}${PROJECT}${RED}\tobject files have been deleted${NNN}"

fclean:
	@rm -f ${NAME}
	@echo "${GRA}${PROJECT}${RED}\tarchive file ${GRA}${NAME}${RED}\t"\
		"has been deleted${NNN}"

re: fclean all

# ---------------------------------------------------------------------------- #
