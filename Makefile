# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 20:49:38 by ampjimen          #+#    #+#              #
#    Updated: 2024/06/24 20:06:56 by ampjimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
 
SRCS_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/

INC = philo.h
SRCS = check.c \
        main.c \
        parser.c \
        tasks.c \
        utils.c

OBJ_FILES = $(SRCS:.c=.o)

SRC = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES = $(addprefix $(INC_DIR), $(INC))

SANITIZE = -g3 -fsanitize=thread
SANITIZE1 = -g3 -fsanitize=address
SANITIZE = -g3

GCC = gcc
CFLAGS = -Wall -Wextra -Werror $(SANITIZE) -pthread -Ofast -march=native -g3
IFLAGS = -I $(INC_DIR)

RM = rm -f

# Colors
RED := "\033[1;31m"
GREEN := "\033[1;32m"
PURPLE := "\033[1;35m"
CYAN := "\033[1;36m"
EOC := "\033[0;0m"

FUNNY_MSG :=$(RED) "\
────────────────────────────────────────────────\n \
░███░█░█░█░█░░░███░███░███░███░█░█░███░███░███░░\n \
░█░█░█░█░█░█░░░█░█░█░░░█░█░█░█░█░█░█░░░█░█░█░░░░\n \
░███░███░█░█░░░█░█░███░█░█░███░███░██░░███░███░░\n \
░█░░░█░█░█░█░░░█░█░░░█░█░█░█░░░█░█░█░░░██░░░░█░░\n \
░█░░░█░█░█░███░███░███░███░█░░░█░█░███░█░█░███░░\n \
────────────────────────────────────────────────\n \
" 
READY_MSG :=$(GREEN) "Execute: ./philo " $(EOC)

# Reglas de construcción
all: obj $(NAME)

$(NAME): $(OBJS)
	@$(GCC) $(OBJS) $(CFLAGS) -o $(NAME) -pthread
	@echo $(FUNNY_MSG)
	@echo $(READY_MSG)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)
	@$(GCC) $(CFLAGS) $(IFLAGS) -o $@ -c $<


# Rules valgrind
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME) 1 1 1 1 1
	@cat valgrind-out.txt

clean:
	@echo $(PURPLE) Erasing... $(EOC)
	@$(RM) -Rf $(OBJ_DIR)

fclean: clean
	@echo $(PURPLE) FClean... $(EOC)
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind


