# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 10:49:05 by dlu               #+#    #+#              #
#    Updated: 2023/06/09 12:11:16 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	so_long

SRCDIR	:=	srcs
_SRC	:=	main.c utils.c map.c mlx_hook.c
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
LFLAGS	:= -L $(LIBDIR) -L $(MLXDIR) -lft -lm -lmlx42 -ldl -lglfw -pthread
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
