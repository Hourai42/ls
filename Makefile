# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttran <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/27 03:17:02 by ttran             #+#    #+#              #
#    Updated: 2018/02/27 03:17:05 by ttran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS_DIR = ./srcs/
INCLUDES = ./includes/
RM = /bin/rm -f
FILES = ft_ls linked_list
CFILES = $(patsubst %, $(SRCS_DIR)%.c, $(FILES))
OFILES = $(patsubst %, %.o, $(FILES))
CFLAGS = -Wall -Wextra -Werror

#libft
LFT = ./libft/
LFT_LIB = $(addprefix $(LFT), ft.a)
LFT_INC = -I $(LFT)
LFT_LINK = -L $(LFT) -l ft

#ft_printf
PRINTF = ./ft_printf/
PRINT_INC = -I $(LFT)$(PRINTF)

all: $(LFT_LIB) $(NAME)

$(LFT_LIB):
	@make -C $(LFT)

$(OFILES):
	@gcc $(CFLAGS) -c -I $(INCLUDES) $(LFT_INC) $(PRINT_INC) $(CFILES)

$(NAME): $(OFILES)
	@gcc $(CFLAGS) $(OFILES) $(LFT_LINK) -o $(NAME)

clean:
	@make -C $(LFT) clean
	@$(RM) $(OFILES)

fclean: clean
	@make -C $(LFT) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
