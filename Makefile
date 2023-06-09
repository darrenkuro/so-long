# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 10:49:05 by dlu               #+#    #+#              #
#    Updated: 2023/06/09 09:39:54 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	so_long

SRCDIR	:=	srcs
_SRC	:=	main.c utils.c map.c
SRC		:=	$(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR	:=	objs
_OBJ	:=	$(_SRC:.c=.o)
OBJ		:=	$(addprefix $(OBJDIR)/, $(_OBJ))

LIBDIR	:=	libft
LIBNAME	:=	libft.a
LIBFT	:=	$(addprefix $(LIBDIR)/, $(LIBNAME))

CC		:=	cc
RM		:=	/bin/rm -f
#CFLAGS	:=	-Wall -Wextra -Werror -g
CFLAGS := -g
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L $(LIBDIR) -lft -lm -I $(LIBDIR)

$(BONUS): $(LIBFT) $(BOBJ)
	$(CC) $(CFLAGS) -o $@ $(BOBJ) -L $(LIBDIR) -lft -lm -I $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(LIBDIR)

$(LIBFT):
	@make -C $(LIBDIR) $(LIBNAME) >/dev/null

clean:
	@make -C $(LIBDIR) $@ >/dev/null
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@make -C $(LIBDIR) $@ >/dev/null
	$(RM) $(NAME) $(BONUS)

re: fclean all

bonus: $(NAME)

var-%:
	@echo $($*)

.PHONY: all clean fclean re bonus libft var-%
