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
NC := \033[0m
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

SRCS_DIR := srcs/
SRCS_LST := parser.c handling_oper.c new_node.c pars_syntax.c pars_utils.c store_data.c foundpath.c\
			split_cmd.c
SRCS := ${addprefix ${SRCS_DIR}, ${SRCS_LST}}

OBJS_DIR := objs/
OBJS_LST := ${patsubst %.c, %.o, ${SRCS_LST}}
OBJS := ${addprefix ${OBJS_DIR}, ${OBJS_LST}}

PROJECT 	:= parser
HEADER		:= parser.h
NAME		:= libparser.a

# ---------------------------------------------------------------------------- #
.PHONY: all clean fclean re title 

all: title ${NAME}
title:
	@printf "\n${YEL}\033[4mEntering ${GRA}${PROJECT}${YEL}'s makefile:${NC}\t"

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADER}
	@ar -rcs ${NAME} ${OBJS}
	@printf "\n$(CYN)Archive file $(GRA)$(NAME)$(CYN) created successfully$(NC)\n"

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${HEADER}
	@${CC} ${CC_FLAGS} -c $< -o $@
	@printf "${GRN}X${NC}"

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)

clean:
	@rm -rf ${OBJS_DIR}
	@echo "${GRA}${PROJECT}${RED}\t\tobject files have been deleted${NC}"

fclean:
	@rm -f ${NAME}
	@echo "${GRA}${PROJECT}${RED}\t\tarchive file ${GRA}${NAME}${RED}\t"\
		"has been deleted${NC}"

re: fclean all

# ---------------------------------------------------------------------------- #
