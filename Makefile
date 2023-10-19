# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:55:16 by itan              #+#    #+#              #
#    Updated: 2023/10/17 19:03:42 by itan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt
BNAME	= minirt_bonus
TNAME	= test.out

MSRC_DIR	= src_mandatory
BSRC_DIR	= src_bonus
SSRC_DIR	= src_shared
TSRC_DIR	= src_test

OBJ_DIR	= obj

MOBJ_DIRS	= $(addprefix $(OBJ_DIR)/, $(shell find $(MSRC_DIR) -type d))
BOBJ_DIRS	= $(addprefix $(OBJ_DIR)/, $(shell find $(BSRC_DIR) -type d))
SOBJ_DIRS	= $(addprefix $(OBJ_DIR)/, $(shell find $(SSRC_DIR) -type d))
TOBJ_DIRS	= $(addprefix $(OBJ_DIR)/, $(shell find $(TSRC_DIR) -type d))

Msrc	= $(shell find $(MSRC_DIR) -name '*.c')
Bsrc 	= $(shell find $(BSRC_DIR) -name '*.c')	
Ssrc	= $(shell find $(SSRC_DIR) -name '*.c')
TsrcCpp	= $(shell find $(TSRC_DIR) -name '*.cpp')
Tsrc	= $(shell find $(TSRC_DIR) -name '*.c')

BUILD_TYPE	= A

m::		BUILD_TYPE = M
b::		BUILD_TYPE = B
t::		BUILD_TYPE = T

# this is for mirroring the out dir and src dir
ifeq ($(BUILD_TYPE), M)
OBJ_DIRS	= $(MOBJ_DIRS) $(SOBJ_DIRS)
MSRC		= $(Msrc) $(Ssrc)
MOBJ		= $(addprefix $(OBJ_DIR)/, $(MSRC:.c=.o))
else ifeq ($(BUILD_TYPE), B)
OBJ_DIRS	= $(BOBJ_DIRS) $(SOBJ_DIRS)
BSRC		= $(Bsrc) $(Ssrc)
MOBJ		= $(addprefix $(OBJ_DIR)/, $(MSRC:.c=.o))
else
OBJ_DIRS	= $(MOBJ_DIRS) $(BOBJ_DIRS) $(SOBJ_DIRS)
MSRC		= $(Msrc) $(Ssrc)
BSRC		= $(Bsrc) $(Ssrc)
MOBJ		= $(addprefix $(OBJ_DIR)/, $(MSRC:.c=.o))
BOBJ		= $(addprefix $(OBJ_DIR)/, $(BSRC:.c=.o))
TSRC		= $(TsrcCpp) $(Tsrc) $(Ssrc)
TOBJ		= $(addprefix $(OBJ_DIR)/, $(Ssrc:.c=.o)) $(addprefix $(OBJ_DIR)/, $(Tsrc:.c=.o)) $(addprefix $(OBJ_DIR)/, $(TsrcCpp:.cpp=.o))
endif

AR		= ar -rcs
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f
HEADERS	= $(shell find includes -type f -name '*.h')
INC		= $(addprefix -I , $(shell find includes -type d -name includes))

LIBDIR	= includes/libft
LIB		= -L$(LIBDIR) -lft -lm
LIBNAME	= libft.a
# this is for debugging
DMNAME	= dm.out
DBNAME	= db.out
DDIR	= test
DFLAGS	= -fsanitize=address -fdiagnostics-color=always -g3

UNAME := $(shell uname)

mlxlib		= ./includes/minilibx_opengl/libmlx.a

ifeq ($(UNAME), Linux)
MLXLIB	= -I /usr/local/include -L/usr/local/lib -lbsd -lmlx -lXext -lX11
endif
ifeq ($(UNAME), Darwin)
INC += -I /usr/local/include 
CFLAGS += -D __APPLE__
MLXLIB	= -I./includes/minilibx_opengl/ -L./includes/minilibx_opengl -lmlx -framework OpenGL -framework AppKit
mlx = $(mlxlib)
endif


# ** COLORS ** #
BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m
B_BLACK		= \033[40m
B_RED		= \033[41m
B_GREEN		= \033[42m
B_YELLOW	= \033[43m
B_BLUE		= \033[44m
B_MAGENTA	= \033[45m
B_CYAN		= \033[46m
B_WHITE		= \033[47m
BRIGHT		= \033[1m
NORMAL		= \033[0m
BLINK		= \033[4m
REVERSE		= \033[5m
UNDERLINE	= \033[3m

all::
		@printf "$(CLR_TERM)$(WHITE)$(BRIGHT) __________________________________ $(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT)< Trying my best to make $(CYAN)$(NAME) & $(BNAME)$(WHITE) >$(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT) ---------------------------------- $(NORMAL)\n"
		@printf "        \ $(GREEN)$(BRIGHT)  ^__^$(NORMAL)\n"
		@printf "         \ $(GREEN)$(BRIGHT) (oo)\_______$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT) (__)\       )\/\$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||----w |$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||     ||$(NORMAL)\n\n"

bonus::	$(BNAME)

m::		
		@printf "$(CLR_TERM)$(WHITE)$(BRIGHT) __________________________________ $(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT)< Trying my best to make $(CYAN)$(NAME)$(WHITE) >$(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT) ---------------------------------- $(NORMAL)\n"
		@printf "        \ $(GREEN)$(BRIGHT)  ^__^$(NORMAL)\n"
		@printf "         \ $(GREEN)$(BRIGHT) (oo)\_______$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT) (__)\       )\/\$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||----w |$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||     ||$(NORMAL)\n\n"
b::		
		@printf "$(CLR_TERM)$(WHITE)$(BRIGHT) __________________________________ $(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT)< Trying my best to make $(CYAN)$(BNAME)$(WHITE) >$(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT) ---------------------------------- $(NORMAL)\n"
		@printf "        \ $(GREEN)$(BRIGHT)  ^__^$(NORMAL)\n"
		@printf "         \ $(GREEN)$(BRIGHT) (oo)\_______$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT) (__)\       )\/\$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||----w |$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||     ||$(NORMAL)\n\n"

m::		$(NAME)
b::		$(BNAME)
all::	$(NAME) $(BNAME)

t::		$(TNAME)

dm::	debug $(DMNAME)
db::	debug $(DBNAME)
da::	debug $(DMNAME) $(DBNAME)

debug::
		@printf "$(CLR_TERM)$(WHITE)$(BRIGHT) ______________________________ $(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT)< Trying my best to make $(CYAN)$(DNAME)$(WHITE) >$(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT) ------------------------------ $(NORMAL)\n"
		@printf "        \ $(GREEN)$(BRIGHT)  ^__^$(NORMAL)\n"
		@printf "         \ $(GREEN)$(BRIGHT) (oo)\_______$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT) (__)\       )\/\$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||----w |$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||     ||$(NORMAL)\n\n"

$(OBJ_DIR)/%.o:	%.c $(HEADERS)
				@mkdir -p $(OBJ_DIRS)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) src objects..." $@
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(TOBJ_DIRS)/%.o:	$(TSRC_DIR)/%.cpp $(HEADERS)
				@mkdir -p $(TOBJ_DIRS)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) src objects..." $@
				@g++ -std=c++14 $(INC) -c $< -o $@

$(DDIR)/%.o:	$(DDIR)/%.c
				@mkdir -p $(DDIR)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) debug objects..." $@
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(mlx) $(LIBDIR)/$(LIBNAME) $(MOBJ) 
			@printf "\n$(MAGENTA)$(BRIGHT)Compiling $(NAME)...          \n"
			@$(CC) $(CFLAGS) $(MOBJ) $(INC) -o $(NAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(BNAME):	$(mlx) $(LIBDIR)/$(LIBNAME) $(BOBJ)
			@printf "\n$(MAGENTA)$(BRIGHT)Compiling $(BNAME)...          \n"
			@$(CC) $(CFLAGS) $(BOBJ) $(INC) -o $(BNAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(DMNAME):	$(mlx) $(MSRC) $(DSRC) $(LIBDIR)/$(LIBNAME) $(HEADERS)
			@printf "\n$(MAGENTA)Compiling $(DMNAME) for $(NAME)...          \n"
			@$(CC) $(CFLAGS) $(DFLAGS) $(INC) $(MSRC) $(DSRC) -o $(DMNAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(DBNAME):	$(mlx) $(BSRC) $(DSRC) $(LIBDIR)/$(LIBNAME) $(HEADERS)
			@printf "\n$(MAGENTA)Compiling $(DBNAME) for $(NAME)...          \n"
			@$(CC) $(CFLAGS) $(DFLAGS) $(INC) $(BSRC) $(DSRC) -o $(DBNAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(TNAME):	$(mlx) $(LIBDIR)/$(LIBNAME) $(TOBJ) 
			@printf "\n$(MAGENTA)Compiling $(TNAME) for $(NAME)...          \n"
			@g++ -std=c++14 $(TOBJ) $(INC) -o $(TNAME) $(LIB) $(MLXLIB)
			@printf "$(GREEN)COMPLETE!!\n\n"

$(LIBDIR)/$(LIBNAME):
		@make -C $(LIBDIR) --no-print-directory

$(mlx):
		@make -C ./includes/minilibx_opengl --no-print-directory

clean:
		@printf "$(RED)$(BRIGHT)Removing $(NAME) objects...\n$(NORMAL)"
		@make clean -C $(LIBDIR) --no-print-directory
		@$(RM) $(MOBJ) $(DOBJ)
		@$(RM) -r $(OBJ_DIR)

fclean:	clean
		@printf "$(RED)$(BRIGHT)Deleting $(NAME), $(BNAME), $(DMNAME), and $(DBNAME)...\n\n$(NORMAL)"
		@make fclean -C $(LIBDIR) --no-print-directory
		@$(RM) $(NAME)
		@$(RM) $(BNAME)
		@$(RM) $(DMNAME)
		@$(RM) $(DBNAME)

re:			fclean all

.PHONY: all clean fclean re debug bonus norm

norm:
		@norminette $(SRC_DIR) includes/
