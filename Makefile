NAME = ft_malcolm

LCYAN = \033[1;36m
GREEN = \033[0;32m
LGREEN = \033[1;32m
LRED = \033[1;31m
RESET = \033[0m
GRAY = \033[90m
PURPLE = \033[0;35m

INFO = $(LCYAN)/INFO/$(RESET)
CLEANING = $(LRED)[DELETING]$(RESET)
SUCCESS = $(LGREEN)[SUCCESS]$(RESET)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = OctoLIB/

FT = // Add functions files with their path here (Be sure to put it in a "src" directory)

SOURCES = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FT)))
OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FT)))

LIB = $(LIB_DIR)libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@if [ -d ./$(LIB_DIR) ]; then \
		echo "$(INFO)$(PURPLE) Updating OctoLIB$(RESET)"; \
		cd $(LIB_DIR) && git fetch -q origin && git reset -q --hard origin/main; \
		echo "$(GREEN)SUCCESS"; \
	else \
		echo "$(INFO)$(PURPLE) Clonning lib...$(RESET)"; \
		git clone git@github.com:mkaliszc/OctoLIB.git; \
	fi
	@echo "$(INFO)$(PURPLE) Making Lib$(RESET)"
	@$(MAKE) -sC $(LIB_DIR)

$(NAME): $(LIB) $(OBJS)
	@echo "$(INFO) $(GREEN)Creating $(NAME)$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)
	@echo "$(SUCCESS)"

clean:
	@echo "$(CLEANING) $(GRAY)$(OBJ_DIR) in $(LIB_DIR) and local dir$(RESET)"
	@$(MAKE) clean -sC $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(CLEANING) $(GRAY)$(NAME) and Lib in $(LIB_DIR)$(RESET)"
	@$(MAKE) fclean -sC $(LIB_DIR)
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re bonus
