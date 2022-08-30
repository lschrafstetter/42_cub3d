# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 11:16:12 by lschrafs          #+#    #+#              #
#    Updated: 2022/08/30 10:15:49 by lschrafs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

COMPILER 	= cc
CFLAGS 		= #-Wall -Wextra -Werror

MYLIBS 		= libft/libft.a
LIBS 		= -lm

SRCS_PATH 	= ./src/
SRCS_NAMES	= main

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBS += -lmlx -lX11 -lXext
	SRCS_NAMES += 
endif
ifeq ($(OS), Darwin)
	LIBS +=  ext/libmlx.a -L./ext/ -lmlx -framework OpenGL -framework AppKit
	SRCS_NAMES += 
endif

SRCS		= $(addprefix $(SRCS_PATH), $(SRC_NAMES))

OBJS_PATH	= ./obj/
OBJS_NAMES	= $(SRCS_NAMES:%=%.o)
OBJS		= $(addprefix $(OBJS_PATH), $(OBJS_NAMES))

all: $(NAME)

$(NAME): $(OBJS) $(MYLIBS)
	$(COMPILER) $(CFLAGS) $(OBJS) $(MYLIBS) $(LIBS) -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir -p $(OBJS_PATH)
	$(COMPILER) $(CFLAGS) -c $< -o $@

$(MYLIBS): FORCE
	make -C $(dir $@)

FORCE: ;

clean:
	rm -rf $(OBJS_PATH)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all