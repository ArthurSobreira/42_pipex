NAME = pipex
NAME_BONUS = pipex_bonus
CFLAGS = -Wall -Wextra -Werror -O3 -g3 
VALGRIND_LOG = valgrind.log

# Paths for libraries
LIB_PATH = ./libs/libft
LIB_NAME = libft.a

# Colors Definition 
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths Definitions
HEADER_PATH = ./includes
BIN_PATH = ./bin/
MANDATORY_SOURCES_PATH = ./src/mandatory/
BONUS_SOURCES_PATH = ./src/bonus/

MANDATORY_SOURCES = \
	clear.c \
	commands.c \
	error.c \
	execute.c \
	main.c \
	start_files.c

BONUS_SOURCES = \
	clear_bonus.c \
	commands_bonus.c \
	error_bonus.c \
	execute_bonus.c \
	here_doc_bonus.c \
	main_bonus.c \
	start_files_bonus.c

OBJECTS = $(addprefix $(BIN_PATH), $(MANDATORY_SOURCES:%.c=%.o))
BONUS_OBJECTS = $(addprefix $(BIN_PATH), $(BONUS_SOURCES:%.c=%.o))

all: libft $(BIN_PATH) $(NAME)

libft:
ifeq ($(wildcard $(LIB_PATH)/$(LIB_NAME)),)
	@make -C $(LIB_PATH) --no-print-directory
	@make get_next_line -C $(LIB_PATH) --no-print-directory
	@make ft_printf -C $(LIB_PATH) --no-print-directory
endif

$(BIN_PATH)%.o: $(MANDATORY_SOURCES_PATH)%.c
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)
	@echo " "

$(NAME): $(OBJECTS)
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| PIPEX executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L $(LIB_PATH) -lft
	@echo " "

bonus: libft $(BIN_PATH) $(NAME_BONUS)

$(BIN_PATH)%.o: $(BONUS_SOURCES_PATH)%.c
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)
	@echo " "

$(NAME_BONUS): $(BONUS_OBJECTS)
	@echo $(CYAN)" ----------------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| PIPEX_BONUS executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------------"$(COLOR_LIMITER)
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BONUS_OBJECTS) -L $(LIB_PATH) -lft
	@echo " "

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

valgrind: all
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--track-fds=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME) infile "cat" "grep teste" outfile
	@cat $(VALGRIND_LOG) 

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	@make clean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(BIN_PATH)

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@rm -rf $(VALGRIND_LOG)

re: fclean
	@make --no-print-directory

re_bonus: fclean
	@make bonus --no-print-directory

.PHONY: all clean fclean re libft bonus re_bonus valgrind
