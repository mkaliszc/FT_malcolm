# ============================================================================ #
#                                    NAME                                      #
# ============================================================================ #

NAME        = ft_malcolm
TARGET_NAME = target

# ============================================================================ #
#                               COLOR / DEBUG                                  #
# ============================================================================ #

LCYAN  = \033[1;36m
GREEN  = \033[0;32m
LGREEN = \033[1;32m
LRED   = \033[1;31m
RESET  = \033[0m
GRAY   = \033[90m
PURPLE = \033[0;35m
INFO     = $(LCYAN)/INFO/$(RESET)
CLEANING = $(LRED)[DELETING]$(RESET)
SUCCESS  = $(LGREEN)[SUCCESS]$(RESET)

# ============================================================================ #
#                               COMPILER / TOOLS                               #
# ============================================================================ #

DOCKER_CMD  = docker compose
DOCKER_PATH = docker-compose.yml
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude

# ============================================================================ #
#                               DIRECTORIES                                    #
# ============================================================================ #

MALCOLM_SRC_DIR = src/malcolm
TARGET_SRC_DIR  = src/target
COMMON_SRC_DIR	= src/common
OBJ_DIR         = obj
LIB_DIR         = OctoLIB/

# ============================================================================ #
#                               SOURCE FILES                                   #
# ============================================================================ #

MALCOLM_SRCS := $(shell find $(MALCOLM_SRC_DIR) -name "*.c")
TARGET_SRCS  := $(shell find $(TARGET_SRC_DIR)  -name "*.c")
COMMON_SRCS	 := $(shell find $(COMMON_SRC_DIR) -name "*.c")

MALCOLM_OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(MALCOLM_SRCS))
TARGET_OBJS  := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(TARGET_SRCS))
COMMON_OBJS  := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(COMMON_SRCS))

LIB = $(LIB_DIR)libft.a

# ============================================================================ #
#                                  RULES                                       #
# ============================================================================ #

# === all ===
all: up

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# === LIB ===
$(LIB):
	@if [ -d ./$(LIB_DIR) ]; then \
		echo "$(INFO)$(PURPLE) Updating OctoLIB$(RESET)"; \
		cd $(LIB_DIR) && git fetch -q origin && git reset -q --hard origin/main; \
		echo "$(GREEN)SUCCESS"; \
	else \
		echo "$(INFO)$(PURPLE) Clonning lib...$(RESET)"; \
		git clone https://github.com/mkaliszc/OctoLIB.git; \
	fi
	@echo "$(INFO)$(PURPLE) Making Lib$(RESET)"
	@$(MAKE) -sC $(LIB_DIR)

# === BINARIES ===
$(NAME): $(LIB) $(MALCOLM_OBJS) $(COMMON_OBJS)
	@echo "$(INFO) $(GREEN)Creating $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(COMMON_OBJS) $(MALCOLM_OBJS) $(LIB)
	@echo "$(SUCCESS)"

$(TARGET_NAME): $(LIB) $(TARGET_OBJS) $(COMMON_OBJS)
	@echo "$(INFO) $(GREEN)Creating $(TARGET_NAME)$(RESET)"
	@$(CC) $(CFLAGS) -o $(TARGET_NAME) $(COMMON_OBJS) $(TARGET_OBJS) $(LIB)
	@echo "$(SUCCESS)"

# === DOCKER ===
up:
	${DOCKER_CMD} -p ${NAME} -f ${DOCKER_PATH} up -d --build
down:
	${DOCKER_CMD} -p ${NAME} -f ${DOCKER_PATH} down -v
stop:
	${DOCKER_CMD} -p ${NAME} -f ${DOCKER_PATH} stop
run:
	${DOCKER_CMD} -p ${NAME} -f ${DOCKER_PATH} start
restart:
	${DOCKER_CMD} -p ${NAME} -f ${DOCKER_PATH} restart

# === CLEAN ===
clean:
	@echo "$(CLEANING) $(GRAY)$(OBJ_DIR) in $(LIB_DIR) and local dir$(RESET)"
	@$(MAKE) clean -sC $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(CLEANING) $(GRAY)$(NAME), $(TARGET_NAME) and Lib in $(LIB_DIR)$(RESET)"
	@$(MAKE) fclean -sC $(LIB_DIR)
	rm -f $(NAME) $(TARGET_NAME)

re: fclean all

.PHONY: all clean fclean re up down run stop restart