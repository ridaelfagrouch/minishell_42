CFILES = minishell.c lexer.c

OFILES = ${CFILES:.c=.o}

CC = gcc
W = -Wall -Werror -Wextra
INC = minishell.h
NAME = minishell

YELLOW=\033[1;33m
NC=\033[0m
GREEN=\033[0;32m
RED=\033[0;31m
DARKVIOLET=\033[1;5;1;36m

define HEADER_M

+ ---------------------------------------------------------------------------- +
|   __   __  __   __    _  ___   _______  __   __  _______  ___      ___       |
|  |  |_|  ||  | |  |  | ||   | |       ||  | |  ||       ||   |    |   |      |
|  |       ||  | |   |_| ||   | |  _____||  |_|  ||    ___||   |    |   |      |
|  |       ||  | |       ||   | | |_____ |       ||   |___ |   |    |   |      |
|  |       ||  | |  _    ||   | |_____  ||       ||    ___||   |___ |   |___   |
|  | ||_|| ||  | | | |   ||   |  _____| ||   _   ||   |___ |       ||       |  |
|  |_|   |_||__| |_|  |__||___| |_______||__| |__||_______||_______||_______|  |
|                                                                              |
+ ---------------------------------------------------------------------------- +${YELLOW} by rel-fagr${NC}

endef
export HEADER_M

.PHONY: all clean fclean re print_header_m

all : ${NAME}

${NAME} : print_header_m ${OFILES}
	@make -C ../libft
	@$(CC) $(OFILES) ../libft/libft.a -lreadline -o $(NAME) -g
	@echo "${YELLOW}$(NAME) created 👍 ${NC}"

print_header_m:
	@echo " ${DARKVIOLET}$$HEADER_M${NC} "

%.o:%.c ${INC}
	@${CC} ${W} -o $@ -c $<
	@echo "${GREEN}$@ created ✅${NC}"

clean:
	@rm -f *.o

fclean : clean
	@rm -f ${NAME}

re : fclean all