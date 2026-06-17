# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efsilva- <efsilva-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/24 00:00:00 by efsilva-          #+#    #+#              #
#    Updated: 2026/06/15 13:09:05 by efsilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDES= -I./includes -I./libft -I./minilibx-linux
LFLAGS	= -lm -lX11 -lXext

OBJ_DIR	= obj
LFT_DIR	= libft
MLX_DIR	= minilibx-linux

SRCS	= src/game/main.c \
		  src/game/init.c \
		  src/parser/parse_config.c \
		  src/parser/parse_map.c \
		  src/parser/valid_map.c \
		  src/parser/valid_close.c \
		  src/parser/utils_parser.c \
		  src/render/render.c

OBJS	= $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

LFT		= $(LFT_DIR)/libft.a
MLX		= $(MLX_DIR)/libmlx.a

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
CYAN	= \033[0;36m
RESET	= \033[0m

all: banner $(LFT) $(MLX) $(NAME)

banner:
	@echo "$(CYAN)"
	@echo " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo "$(RESET)"
	@echo "$(YELLOW)         🎮  My first RayCaster  🎮$(RESET)"
	@echo "$(GREEN)         ══════════════════════════$(RESET)"
	@echo ""

$(LFT):
	@echo "$(BLUE)📚 Compiling libft...$(RESET)"
	@$(MAKE) -C $(LFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ libft compiled!$(RESET)"

$(MLX):
	@echo "$(BLUE)📚 Compiling minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo "$(GREEN)✅ minilibx compiled!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LFT) $(MLX) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory
	@echo "$(GREEN)✅ Cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✅ $(NAME) removed!$(RESET)"

re: fclean all

bonus: all

norm:
	@echo "$(CYAN)📏 Checking Norminette...$(RESET)"
	@norminette src includes $(LFT_DIR)

.PHONY: all clean fclean re bonus banner norm