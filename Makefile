# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 10:49:05 by dlu               #+#    #+#              #
#    Updated: 2023/06/10 12:34:19 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	so_long

SRCDIR	:=	srcs
_SRC	:=	main.c utils.c map.c mlx_hook.c action.c
SRC		:=	$(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR	:=	objs
_OBJ	:=	$(_SRC:.c=.o)
OBJ		:=	$(addprefix $(OBJDIR)/, $(_OBJ))

LIBDIR	:=	libft
LIBNAME	:=	libft.a
LIBFT	:=	$(addprefix $(LIBDIR)/, $(LIBNAME))

MLXDIR	:=	MLX42
LIBMLX	:=	$(addprefix $(MLXDIR)/, libmlx42.a)

CC		:=	cc
RM		:=	/bin/rm -f
CFLAGS	:=	-Wall -Wextra -Werror -g

ifeq ($(shell uname -s), Darwin)
	LFLAGS	:=	-L $(LIBDIR) -L $(MLXDIR) -lft -lmlx42 -lglfw \
				-L "/opt/homebrew/Cellar/glfw/3.3.8/lib"
else ifeq ($(shell uname -s), Linux)
	LFLAGS	:=	-L $(LIBDIR) -L $(MLXDIR) -lft -lm -lmlx42 -ldl -lglfw \
				-pthread
endif

IFLAGS	:= -I $(LIBDIR) -I $(MLXDIR)/include

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(BONUS): $(LIBFT) $(BOBJ)
	$(CC) $(CFLAGS) -o $@ $(BOBJ) $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(IFLAGS)

$(LIBFT):
	@make -C $(LIBDIR) $(LIBNAME) >/dev/null

$(LIBMLX):
	@git submodule init >/dev/null && git submodule update >/dev/null
	@cd $(MLXDIR) && cmake -B . >/dev/null && cmake --build . -j4 >/dev/null

clean:
	@make -C $(LIBDIR) $@ >/dev/null
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@make -C $(LIBDIR) $@ >/dev/null
	$(RM) $(LIBMLX)
	$(RM) $(NAME) $(BONUS)

re: fclean all

bonus: $(NAME)

var-%:
	@echo $($*)

.PHONY: all clean fclean re bonus libft var-%
