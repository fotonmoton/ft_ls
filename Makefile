# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 16:54:48 by gtertysh          #+#    #+#              #
#    Updated: 2017/03/25 18:32:30 by gtertysh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# color constants

SWITCH =			\033[

NORMAL =			$(SWITCH)0m
GREEN =				$(SWITCH)32m
BLUE =				$(SWITCH)34m
CYAN =				$(SWITCH)36m

# final binary name

NAME = 				ft_ls

# static libraries

LIBFT =				libft.a

# directories

SRC_DIR =			./src/
OBJ_DIR =			./obj/
LIBFT_DIR =			./libft/

# src and obj files

SRC_FILES =			$(shell ls $(SRC_DIR))
OBJ_FILES =			$(SRC_FILES:.c=.o)

SRC =				$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ =				$(addprefix $(OBJ_DIR), $(OBJ_FILES))

# header files and directories

HEADER =			ft_ls.h
FT_LS_INC =			./inc/
LIBFT_INC =			$(LIBFT_DIR)includes/
INC =				-I $(LIBFT_DIR) -I $(FT_LS_INC) 

# compiler flags

# for valgrind debugging uncomment $(DEBUG) flag.
# command for generate output:
# valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes program arguments

LIBFT_FLAGS =		-lft -L $(LIBFT_DIR)
CC_FLAGS =			-Werror -Wextra -Wall
DEBUG = 			-g
OPT = 				-O3
FLAGS :=			$(CC_FLAGS)		\
					$(LIBFT_FLAGS)	\
					$(OPT)			\
					$(DEBUG)

# compiler

CC =				gcc

# rules

all: $(NAME)

$(NAME): $(LIBFT_DIR)$(LIBFT) $(OBJ)
	@echo "$(CYAN)Linking binary...$(NORMAL)"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)Done!$(NORMAL)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(FT_LS_INC)$(FT_LS_HEADER)
	@echo "$(CYAN)Compiling object files: $(BLUE)$@$(NORMAL)"
	@$(CC) $(CC_FLAGS) $(OPT) $(INC) -c $< -o $@  

$(LIBFT_DIR)$(LIBFT):
	@echo "$(CYAN)Compiling libft library...$(NORMAL)"
	@make -s -C $(LIBFT_DIR)

$(MLX_DIR)$(MLX):
	@echo "$(CYAN)Compiling libmlx library...$(NORMAL)"
	@make -s -C $(MLX_DIR)
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

libclean:
	@make clean -s -C $(LIBFT_DIR)

libfclean:
	@make fclean -s -C $(LIBFT_DIR)

re: fclean libfclean all

pu: fclean libfclean libclean
	@echo "$(CYAN)Cleaning for push...$(NORMAL)"

