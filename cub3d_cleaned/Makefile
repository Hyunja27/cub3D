NAME = cub3D
LIBFT = libft.a

LIBFT_DIR = ./libft
IMG_DIR = ./img
MLX_DIR = ./mlx
INC_DIR = ./includes
SRC_DIR = ./sources

CC = gcc
GCC_FLAG = -Wall -Wextra -Werror -g
RM = rm
RMFLAGS = -f
AR = ar crs

SRC =  $(addprefix $(SRC_DIR)/, \
		cub3D.c \
		make_2d_map.c \
		make_bmp.c \
		sprite_arrange.c \
		key_input.c \
		screen_control.c \
		map_parsing.c \
		map_parsing_tools_1.c \
		map_parsing_tools_2.c \
		map_parsing_checker.c \
		)

MLX_FLAG = -framework OpenGL -framework Appkit

GREEN = \033[32m
PURPLE = \033[35m
MINT = \033[36m
RED = \033[31m
BLINK = \033[5m
BOLD = \033[1m
BACKGRAY = \033[100m
NO_COLOR = \e[0m

all : $(NAME)

$(NAME) : 
	@echo "${PURPLE}[${RED} Makefile${PURPLE} :starting.. ]"
	@(make -C $(LIBFT_DIR))
	@echo "${PURPLE}->making libft.a , and add src.o.."
	@echo "${PURPLE}->resting.. drinking some coffee..."
	@(cp $(LIBFT_DIR)/$(LIBFT) .)
	$(CC) $(GCC_FLAG) -L $(LIBFT_DIR) -l ft -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -L $(MLX_DIR) -lmlx $(MLX_FLAG) $(SRC) -o cub3D
	@make clean
	@echo "${MINT}making Done."

clean :
	@echo "${PURPLE}[${RED} cleaning ${PURPLE} : erase objects file.]"
	@(make -C $(LIBFT_DIR) clean)
	@echo "${PURPLE}->kill every objects, include libft objects.."
	@echo "${PURPLE}->clearing dead bodys..."
	@echo "${MINT}cleaning Done."

fclean : clean
	@echo "${PURPLE}[${RED} fcleaning ${PURPLE} : erase objects & lib.a file.]"
	@echo "${PURPLE}->kill all lib.a files... bye bye!"
	@($(RM) $(RMFLAGS) $(LIBFT_DIR)/$(LIBFT))
	@($(RM) $(RMFLAGS) $(NAME))
	@($(RM) $(RMFLAGS) $(LIBFT))
	@echo "${MINT}fcleaning Done."

test : 
	@(make fclean)
	@(make)
	@(./cub3D test_map.cub)
	# @(rm cub3D)
	@(rm tmp_map)
	