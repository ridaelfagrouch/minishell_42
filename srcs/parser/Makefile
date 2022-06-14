# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by ███████╗██║       #+#    #+#              #
#    Updated: 2022/06/14 11:23:10 by rel-fagr         ###   ########.fr        #
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
CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror

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
	@echo "\n${YEL}\033[4mEntering ${GRA}${PROJECT}${YEL}'s makefile${NC}\n"

${NAME}: ${OBJS_DIR} ${OBJS} ${HEADER}
	@ar -rcs ${NAME} ${OBJS}
	@echo "$(BLU)Archive file $(GRA)$(NAME)$(BLU) created successfully$(NC)\n"

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${HEADER}
	@${CC} ${CC_FLAGS} -c $< -o $@
	@echo "${MGN}Object file ${GRA}$@${MGN} created from ${GRA}$<${MGN}${NC}"

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
