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
		cub_3d.c \
		make_2d_map.c \
		make_2d_lifebar.c \
		make_bmp.c \
		sprite_arrange.c \
		key_input_1.c \
		key_input_2.c \
		screen_control.c \
		map_parsing.c \
		map_parsing_tools_1.c \
		map_parsing_tools_2.c \
		map_parsing_checker.c \
		make_texture.c \
		main_loop.c \
		make_sprite.c \
		ray_caster.c \
		floor_ceiling_caster.c \
		free_memory.c \
		init_basic.c \
		max_screen.c \
		sound.c \
		animate.c \
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
	@(cp ./mlx_beta/libmlxbeta.dylib .)
	$(CC) $(GCC_FLAG) -L $(LIBFT_DIR) -l ft -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -L $(MLX_DIR) -lmlx -L ./mlx_beta -lmlxbeta $(MLX_FLAG) $(SRC) -o cub3D
	@make clean
	@echo "${MINT}making Done."

clean :
	@echo "${PURPLE}[${RED} cleaning ${PURPLE} : erase objects file.]"
	@(make -C $(LIBFT_DIR) clean)
	@($(RM) $(RMFLAGS) tmp_map)
	@echo "${PURPLE}->kill every objects, include libft objects.."
	@echo "${PURPLE}->clearing dead bodys..."
	@echo "${MINT}cleaning Done."

fclean : clean
	@echo "${PURPLE}[${RED} fcleaning ${PURPLE} : erase objects & lib.a file.]"
	@echo "${PURPLE}->kill all lib.a files... bye bye!"
	@($(RM) $(RMFLAGS) $(LIBFT_DIR)/$(LIBFT))
	@($(RM) $(RMFLAGS) $(NAME))
	@($(RM) $(RMFLAGS) $(LIBFT))
	@($(RM) $(RMFLAGS) libmlxbeta.dylib)
	@echo "${MINT}fcleaning Done."

test : 
	@(make fclean)
	@(make)
	@(./cub3D test_map.cub)
	@(rm tmp_map)
	