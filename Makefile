# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 10:49:05 by dlu               #+#    #+#              #
#    Updated: 2025/06/22 10:13:10 by dlu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	so-long
PROJECT	:=	$$YELLOW[$(NAME)]$$RESET
TARGET	:=	so_long

INCDIR	:=	include

SRCDIR	:=	src
_SRC	:=	main.c utils.c map.c mlx_hook.c action.c
SRC		:=	$(addprefix $(SRCDIR)/,$(_SRC))

OBJDIR	:=	objs
_OBJ	:=	$(_SRC:.c=.o)
OBJ		:=	$(addprefix $(OBJDIR)/,$(_OBJ))

LIBDIR	:=	libft
_LIBFT	:=	libft.a
LIBFT	:=	$(LIBDIR)/$(_LIBFT)

MLXDIR	:=	MLX42
_LIBMLX	:=	libmlx42.a
LIBMLX	:=	$(MLXDIR)/$(_LIBMLX)

CC			:=	cc
RM			:=	/bin/rm -f
CFLAGS		:=	-Wall -Wextra -Werror -g
CPPFLAGS	:= -I $(INCDIR) -I $(LIBDIR)/$(INCDIR) -I $(MLXDIR)/$(INCDIR)

ifeq ($(shell uname -s), Darwin)
	LDFLAGS	:=	-L $(LIBDIR) -L $(MLXDIR) -L "/opt/homebrew/Cellar/glfw/3.4/lib"
	LDLIBS	:=	-lft -lmlx42 -lglfw
else ifeq ($(shell uname -s), Linux)
	LDFLAGS	:=	-L $(LIBDIR) -L $(MLXDIR)
	LDLIBS	:=	-lft -lm -lmlx42 -ldl -lglfw -pthread
endif

PAD_WIDTH		?=	20
.DEFAULT_GOAL	:=	all
.SILENT:

define submodule-target
.PHONY:	$1-init
$1-init:
	if git submodule status "$1" | grep -Eq '^[-+]'; then \
		printf "%-*s 🔄 Initializing submodule $1...\n" $$(PAD_WIDTH) "$$(PROJECT)"; \
		git submodule update --init --recursive $1 2>&1 | sed 's/^/    - /'; \
		printf "%-*s ✅ Git submodule $1 initialized.\n" $$(PAD_WIDTH) "$$(PROJECT)"; \
	fi

.PHONY:	$1-deinit
$1-deinit:
	if [ -f "$1/.git" ]; then \
		printf "%-*s 🧹 Deinitializing $1 submodule...\n" \
		$$(PAD_WIDTH) "$$(PROJECT)"; \
		git submodule deinit -f $1 2>&1 | sed 's/^/    - /'; \
		printf "%-*s ✅ Git submodule $1 deinitialized.\n" \
		$$(PAD_WIDTH) "$$(PROJECT)"; \
	fi
endef

$(eval $(call submodule-target,$(LIBDIR)))
$(eval $(call submodule-target,$(MLXDIR)))

.PHONY: all
all: $(TARGET)

.PHONY: bonus
bonus: $(TARGET)

.PHONY:	$(LIBDIR)-clean
$(LIBDIR)-clean:
	if [ -f $(LIBDIR)/Makefile ]; then \
		$(MAKE) -C $(LIBDIR) clean PAD_WIDTH=$(PAD_WIDTH); \
	fi

.PHONY: clean
clean: $(LIBDIR)-clean
	if [ -d $(OBJDIR) ]; then \
		printf "%-*s 🧹 Removing object files..." $(PAD_WIDTH) "$(PROJECT)"; \
		$(RM) -r $(OBJDIR); \
		echo " ✅ "; \
	fi

.PHONY:	$(LIBDIR)-fclean
$(LIBDIR)-fclean:
	if [ -f "$(LIBDIR)/Makefile" ]; then \
		$(MAKE) -C $(LIBDIR) fclean PAD_WIDTH=$(PAD_WIDTH); \
	fi

#$(RM) $(LIBMLX)
.PHONY: fclean
fclean: clean $(LIBDIR)-fclean
	if [ -f "$(TARGET)" ]; then \
		printf "%-*s 🗑️ Removing binary..." $(PAD_WIDTH) "$(PROJECT)"; \
		$(RM) $(TARGET); \
		echo " ✅ "; \
	fi

.PHONY: re
re: fclean all

.PHONY: var-%
var-%:
	@echo $($*)

$(OBJDIR):
	printf "%-*s 📁 Creating obj directory..." $(PAD_WIDTH) "$(PROJECT)"
	mkdir -p $@
	echo " ✅ "

$(TARGET): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
	printf "%-*s ⚙️ Compiling: $<..." $(PAD_WIDTH) "$(PROJECT)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	echo " ✅ "

$(LIBFT):	| $(LIBDIR)-init
	printf "%-*s ⚙️ Building $(_LIBFT)...\n" $(PAD_WIDTH) "$(PROJECT)"
	$(MAKE) -C "$(LIBDIR)" --silent PAD_WIDTH=$(PAD_WIDTH)
	printf "%-*s ✅ $(_LIBFT) built.\n" $(PAD_WIDTH) "$(PROJECT)"

#cd $(MLXDIR) && cmake -B . >/dev/null && cmake --build . -j4 >/dev/null
$(LIBMLX):	| $(MLXDIR)-init
	printf "%-*s ⚙️ Building $(_LIBMLX)...\n" $(PAD_WIDTH) "$(PROJECT)"
	OUT="$$(cmake -S "$(MLXDIR)" -B "$(MLXDIR)" 2>&1)" && echo "$$OUT" | sed 's/^/    /'
	OUT="$$(cmake --build "$(MLXDIR)" -j4 2>&1)" && echo "$$OUT" | sed 's/^/    /'
	printf "%-*s ✅ $(_LIBMLX) built.\n" $(PAD_WIDTH) "$(PROJECT)"