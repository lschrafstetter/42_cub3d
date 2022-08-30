# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lschrafs <lschrafs@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 11:16:12 by lschrafs          #+#    #+#              #
#    Updated: 2022/08/30 10:56:36 by lschrafs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

COMPILER 	= cc
CFLAGS 		= #-Wall -Wextra -Werror

MYLIBS 		= libft/libft.a
LIBS 		= -lm

SRCS_PATH 	= 	./src/
INIT		=	init/
HOOKS		=	hooks/
RAYCAST		=	raycast/
EXIT		= 	exit/
UTILS		=	utils/


SRCS_NAMES	= 	main \
				$(INIT)init \
				$(EXIT)exit \
				$(EXIT)free \

OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBS += -lmlx -lX11 -lXext
	SRCS_NAMES += $(EXIT)destroy_linux
endif
ifeq ($(OS), Darwin)
	LIBS +=  ext/libmlx.a -L./ext/ -lmlx -framework OpenGL -framework AppKit
	SRCS_NAMES += $(EXIT)destroy_mac
endif

OBJS_PATH	= 	./obj/
OBJS_NAMES	= 	$(SRCS_NAMES:%=%.o)
OBJS		= 	$(addprefix $(OBJS_PATH), $(OBJS_NAMES))

ALL_DIRS	= 	$(INIT) $(HOOKS) $(RAYCAST) $(EXIT) $(UTILS)
DIRS_PATHS	=	$(addprefix $(OBJS_PATH), $(ALL_DIRS))

all: $(NAME)

$(NAME): $(OBJS) $(MYLIBS)
	$(COMPILER) $(CFLAGS) $(OBJS) $(MYLIBS) $(LIBS) -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir -p $(OBJS_PATH)
	mkdir -p $(DIRS_PATHS)
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