################################################################################
################################################################################
##                                                                            ##
##       ███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗       ##
##       ████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝       ##
##       ██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗         ##
##       ██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝         ##
##       ██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗       ##
##       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝       ##
##                                                                            ##
################################################################################
################################################################################

# --------------------------- Terminal Color Codes --------------------------- #
NNN := \033[0m
RED := \033[31m
YEL := \033[33m
GRA := \033[37m
CYN := \033[36m
GRN := \033[32m
MGN := \033[35m
BLU := \033[34m

# ---------------------------------------------------------------------------- #
CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror \
	-I /goinfre/mnaimi/.brew/Cellar/readline/8.1.2/include

SRCS_DIR	:=	srcs/

SRCS_LST	:=	env_init_1st.c env_init_2nd.c \
				exec_cmds.c exec_misc.c builtin_cmds/cd_cmd.c \
				builtin_cmds/echo_cmd.c builtin_cmds/env_cmd.c \
				builtin_cmds/exit_cmd.c builtin_cmds/export_cmd.c \
				builtin_cmds/pwd_cmd.c builtin_cmds/unset_cmd.c \
				executor.c redir_and_pipe.c signal_handling.c
SRCS		:=	${addprefix ${SRCS_DIR}, ${SRCS_LST}}

OBJS_DIR	:=	objs/
OBJS_LST	:=	${patsubst %.c, %.o, ${SRCS_LST}}
OBJS		:=	${addprefix ${OBJS_DIR}, ${OBJS_LST}}

O_BLTN_DIR	:=	objs/builtin_cmds/

PROJECT :=	executor
HEADER	:=	executor.h
NAME	:=	libexecutor.a

MAIN	:= test_main.c

# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re title test_clean test_compile

all: title ${NAME}

title:
	@printf "\n${YEL}\033[4mEntering ${GRA}${PROJECT}${YEL}'s makefile: ${NNN}\t"

${NAME}: ${OBJS_DIR} ${O_BLTN_DIR} ${OBJS} ${HEADER}
	@ar -rcs ${NAME} ${OBJS}
	@printf "\n$(CYN)Archive file $(GRA)$(NAME)$(CYN) created successfully$(NNN)\n"

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${HEADER}
	@${CC} ${CC_FLAGS} -c $< -o $@
	@printf "${GRN}X${NC}"

${OBJS_DIR}:
	@mkdir ${OBJS_DIR}

${O_BLTN_DIR}:
	@mkdir ${O_BLTN_DIR}

clean:
	@rm -rf ${OBJS_DIR}
	@echo "${GRA}${PROJECT}${RED}\tobject files have been deleted${NNN}"

fclean: clean
	@rm -f ${NAME}
	@echo "${GRA}${PROJECT}${RED}\tarchive file ${GRA}${NAME}${RED}\t"\
		"has been deleted${NNN}"

re: fclean all

# ---------------------------------------------------------------------------- #

