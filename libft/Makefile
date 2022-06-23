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

# ------------------------------- Color Codes -------------------------------- #
NC := \033[0m
RED := \033[31;1;3m
YEL := \033[33;1;3m
GRA := \033[37;1;3m
CYN := \033[36;1;3m
GRN := \033[32;1;3m
MGN := \033[35;1;3m
BLU := \033[34;1;3m

# -------------------------------- Variables --------------------------------- #
CC := gcc
FLAGS := -Wall -Wextra -Werror

SRCS_DIR := srcs/
SRCS_LST := ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c \
	ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c ft_strstr.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_realloc.c ft_split.c \
	ft_clear_console.c ft_free.c ft_intlen.c ft_isalnum.c ft_isalpha.c \
	ft_abs.c ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_strnstr.c \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_strstr_tl.c
SRCS := ${addprefix ${SRCS_DIR}, ${SRCS_LST}}

OBJS_DIR := objs/
OBJS_LST := ${patsubst %.c, %.o, ${SRCS_LST}}
OBJS := ${addprefix ${OBJS_DIR}, ${OBJS_LST}}

PROJECT := libft
HEADER := libft.h
NAME := libft.a

.PHONY: all clean fclean re title

# ---------------------------------- Recipes --------------------------------- #
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
	@echo "${GRA}${PROJECT}${RED}\t\tarchive file ${GRA}${NAME}${RED}\t\t"\
		"has been deleted${NC}"

re: fclean all