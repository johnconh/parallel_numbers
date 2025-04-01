NAME = parallel_numbers

CC = gcc
CFLAGS= -Wall -Wextra  -pthread -g3  -fsanitize=address -I ./includes

SRCDIR = ./src/
OBJDIR = ./objs/
INCSDIR = ./incs/

SRCS = $(wildcard $(SRCDIR)*.c)
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

DEF_COLOR = \033[0;39m
RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) has been created$(DEF_COLOR)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)Compiling: $< ...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Done!$(DEF_COLOR)"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)$(NAME) objects have been removed$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) has been removed$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re