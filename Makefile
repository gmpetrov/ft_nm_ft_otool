# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/25 20:36:16 by gpetrov           #+#    #+#              #
#    Updated: 2014/04/25 20:56:44 by gpetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_otool
NAME2		= ft_nm
FILES		= main.c ft_otool.c dec_to_hex.c tools.c
FILES2		= main.c
SRCS		= $(addprefix ft_otool_dir/srcs/, $(FILES))
SRCS2	 	= $(addprefix ft_nm_dir/srcs/, $(FILES2))
OBJS		= $(SRCS:ft_otool_dir/srcs/%.c=ft_otool_dir/.obj/%.o)
OBJS2		= $(SRCS:ft_nm_dir/srcs/%.c=ft_otool_dir/.obj/%.o)
INC			= -I ft_otool_dir/includes -I libft/includes
INC2		= -I ft_nm_dir/includes -I libft/includes
FLAGS		=  -Wall -Wextra -Werror -O3
LIB			= -L libft -lft

all: $(NAME) $(NAME2)

$(NAME): $(OBJS) $(OBJS2)
	@make -C libft
	@cc $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB)
	@cc $(FLAGS) $(SRCS2) -o $(NAME2) $(INC2) $(LIB)
	@echo "\n > \033[36mnm-otool\033[m project compilation [\033[32mDONE\033[m]\n"

ft_otool_dir/.obj/%.o: ft_otool_dir/srcs/%.c
	@mkdir -p ft_otool_dir/.obj
	@cc -c $< -o $@ $(FLAGS) $(INC)

ft_nm_dir/.obj/%.o: ft_nm_dir/srcs/%.c
	@mkdir -p ft_nm_dir/.obj
	@cc -c $< -o $@ $(FLAGS) $(INC2)

clean:
	@rm -rf .obj

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@rm -f $(NAME2)
	@echo "fclean : [\033[32mDONE\033[m]"

re: fclean all

