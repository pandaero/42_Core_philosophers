# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pandalaf <pandalaf@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:01:24 by pandalaf          #+#    #+#              #
#    Updated: 2022/11/17 21:18:54 by pandalaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Target output
NAME := philo
# Compiler options
CC := cc
CFLAGS := -Wall -Werror -Wextra
COPT := #-fsanitize=address
# Sources to compile
SRC_DIR := src/
SRC_FILES := philo.c utils.c create.c init.c end.c search.c timing.c assist.c \
				further_utils.c locking.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
# Objects to compile
OBJ_DIR := obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Make desired target
all: directories $(NAME)

# Make the target executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(COPT) -o $(NAME) $^

# Make required directories
directories: $(OBJ_DIR)

# Make object files
$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $^

# Make object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean intermediate files
clean:
	rm -rf $(OBJ_DIR)

# Clean all non-source files
fclean: clean
	rm -f $(NAME)

# Clean everything and recompile
re: fclean all

# Make sure these aren't treated as files
.PHONY: all directories clean fclean re
