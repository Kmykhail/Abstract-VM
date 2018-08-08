# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmykhail <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/07 19:19:07 by kmykhail          #+#    #+#              #
#    Updated: 2018/08/07 19:19:11 by kmykhail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

FLAGS = -Wall -Wextra -Werror

G = g++

DIR_INC = ./includes/
DIR_SRC = ./srcs/
DIR_OBJ = ./obj/

SRC = AbstractVM.cpp Factory.cpp Vector.cpp main.cpp

HPP = IOperand.hpp AbstractVM.hpp Factory.hpp Operand.hpp Vector.hpp

INC_PATH = $(addprefix $(DIR_INC), $(HPP))
OBJ = $(addprefix $(DIR_OBJ), $(SRC:.cpp=.o))
INC = $(addprefix -I, $(DIR_INC))


all: CREATE_OBJ_DIR $(NAME)

CREATE_OBJ_DIR:
	@mkdir  -p $(DIR_OBJ)

$(NAME): $(OBJ)
	@$(G) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "\033[0;33mavm\033[0;32m[OK] \033[0m       \033[0m" $<

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp $(INC_PATH)
	@$(G) $(FLAGS) $(INC) -c -o $@ $<

clean:
	@rm -rf $(DIR_OBJ)
fclean:
	@rm -rf $(DIR_OBJ)
	@rm -rf $(NAME)
re: fclean all