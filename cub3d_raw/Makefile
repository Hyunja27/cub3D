NAME = cub3D

CC = gcc
GCC_FLAG = -Wall -Wextra -Werror

MLX_DIR = ./mlx
MLX_FLAG = -framework OpenGL -framework Appkit

all : $(NAME)

run :
	$(CC) 2d_map.c -L $(MLX_DIR) -l mlx $(MLX_FLAG) 
	./a.out
	rm -rf ./a.out
