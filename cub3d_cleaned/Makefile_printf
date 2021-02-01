NAME = libftprintf.a
LIBFT = libft.a

LIBFT_DIR = ./libft
OBJS_DIR = ./objs
LIBFT_INC_DIR = $(LIBFT_DIR)/includes

INC_DIR = ./includes

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm
RMFLAGS = -f
AR = ar crs

OBJS_FILES = ft_printf \
			ft_width_detecter \
			ft_pharse_str \
			ft_precision_detecter \
			ft_wid_pre_seperater \
			ft_set_clear \
			ft_printf_with_set \
			ft_printf_int \
			ft_printf_str \
			ft_printf_char \
			ft_printf_ptr \
			ft_printf_per \
			ft_printf_hex \
			ft_printf_oct \
			ft_printf_uni \
			ft_printf_double \
			ft_printf_double_g \
			ft_printf_double_e \
			ft_flag_setter \
			ft_flag_setter_double \
			ft_body_setter_int \
			ft_body_setter_str \
			ft_body_setter_hex \
			ft_body_setter_ptr \
			ft_body_setter_double \
			ft_left_setter \
			ft_left_setter_hex \
			ft_left_setter_plus \
			ft_dtoa \
			ft_dtoa_e \
			ft_dtoa_e_big \
			ft_zero_maker \
			ft_array_round \
			ft_manti_to_a_e \
			ft_manti_to_a \
			ft_e_manti_array \
			ft_expond_adder \
			ft_bigint \
			ft_space_adder \
			ft_minus_adder \
			ft_ilencal

OBJS = $(addprefix ./, $(addsuffix .o, $(OBJS_FILES)))

SRC_FILES = ft_printf \
			0_phaser/ft_width_detecter \
			0_phaser/ft_pharse_str \
			0_phaser/ft_precision_detecter \
			0_phaser/ft_wid_pre_seperater \
			0_phaser/ft_set_clear \
			1_divider/ft_printf_with_set \
			2_print_by_type/ft_printf_int \
			2_print_by_type/ft_printf_str \
			2_print_by_type/ft_printf_char \
			2_print_by_type/ft_printf_ptr \
			2_print_by_type/ft_printf_per \
			2_print_by_type/ft_printf_hex \
			2_print_by_type/ft_printf_oct \
			2_print_by_type/ft_printf_uni \
			2_print_by_type/ft_printf_double \
			2_print_by_type/ft_printf_double_g \
			2_print_by_type/ft_printf_double_e \
			3_flag_setter/ft_flag_setter \
			3_flag_setter/ft_flag_setter_double \
			4_body_setter/ft_body_setter_int \
			4_body_setter/ft_body_setter_str \
			4_body_setter/ft_body_setter_hex \
			4_body_setter/ft_body_setter_ptr \
			4_body_setter/ft_body_setter_double \
			5_left_setter/ft_left_setter \
			5_left_setter/ft_left_setter_hex \
			5_left_setter/ft_left_setter_plus \
			6_util/ft_dtoa \
			6_util/ft_dtoa_e \
			6_util/ft_dtoa_e_big \
			6_util/ft_zero_maker \
			6_util/ft_array_round \
			6_util/ft_manti_to_a_e \
			6_util/ft_manti_to_a \
			6_util/ft_e_manti_array \
			6_util/ft_expond_adder \
			6_util/ft_bigint \
			6_util/ft_space_adder \
			6_util/ft_minus_adder \
			6_util/ft_ilencal

SRCS = $(addprefix ./sources/, $(addsuffix .c, $(SRC_FILES)))

GREEN = \033[32m
PURPLE = \033[35m
MINT = \033[36m
RED = \033[31m

BLINK = \033[5m
BOLD = \033[1m
BACKGRAY = \033[100m
NO_COLOR = \e[0m

all : $(NAME)

$(NAME) : $(OBJS) 
	@echo "${PURPLE}[${RED} Makefile${PURPLE} :starting.. ]"
	@(make -C $(LIBFT_DIR))
	@echo "${PURPLE}->making libft.a , and add src.o.."
	@echo "${PURPLE}->resting.. drinking some coffee..."
	@(cp $(LIBFT_DIR)/$(LIBFT) .)
	@(mv $(LIBFT) $(NAME))
	@($(AR) $(NAME) $(OBJS))
	@echo "${MINT}making Done."

$(OBJS) : 
	@$(CC) $(CFLAGS) -I $(LIBFT_INC_DIR) -I $(INC_DIR) -c $(SRCS)

clean :
	@echo "${PURPLE}[${RED} cleaning ${PURPLE} : erase objects file.]"
	@(make -C $(LIBFT_DIR) clean)
	@echo "${PURPLE}->kill every objects, include libft objects.."
	@echo "${PURPLE}->clearing dead bodys..."
	@($(RM) $(RMFLAGS) $(OBJS))
	@echo "${MINT}cleaning Done."

fclean : clean
	@echo "${PURPLE}[${RED} fcleaning ${PURPLE} : erase objects & lib.a file.]"
	@echo "${PURPLE}->kill all lib.a files... bye bye!"
	@($(RM) $(RMFLAGS) $(LIBFT_DIR)/$(LIBFT))
	@($(RM) $(RMFLAGS) $(NAME))
	@echo "${MINT}fcleaning Done."

re : fclean all

bonus : $(NAME)
