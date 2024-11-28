NAME =		philo

CFLAGS =	-Werror -Wall -Wextra # -g -fsanitize=thread

BLUE =		\033[0;34m
GREEN =		\033[0;32m
RESET =		\033[0m

SRC =	src/main.c src/init.c src/utils.c src/routine.c src/actions.c src/check_args.c

OBJ =		${SRC:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	@echo "$(BLUE)Building $(NAME)...$(RESET)"
	@cc $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) built$(RESET)"

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re