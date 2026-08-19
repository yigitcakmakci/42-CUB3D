NAME        = cub3D
NAME_BONUS	= cub3D_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -D_GNU_SOURCE

SRC_DIR     = src
MLX_DIR     = include/minilibx-linux
LIBFT_DIR   = include/libft
HEADERS_DIR = include

LIBFT       = $(LIBFT_DIR)/libft.a

SRCS_COMMON = $(SRC_DIR)/main.c \
              $(SRC_DIR)/parse_checks.c \
              $(SRC_DIR)/parse_textures_colors.c \
              $(SRC_DIR)/parser_core.c \
              $(SRC_DIR)/file_reader.c \
              $(SRC_DIR)/map_validator.c \
              $(SRC_DIR)/get_next_line.c \
			  $(SRC_DIR)/free_game.c \
			  $(SRC_DIR)/dda.c \
			  $(SRC_DIR)/dda_init.c \
			  $(SRC_DIR)/player.c \
			  $(SRC_DIR)/events.c \
			  $(SRC_DIR)/player_update.c \
			  $(SRC_DIR)/texture_init.c \
			  $(SRC_DIR)/texture_draw.c

SRCS_MANDATORY = $(SRC_DIR)/render.c
SRCS_BONUS = $(SRC_DIR)/render_bonus.c \
			 $(SRC_DIR)/minimap_bonus.c

OBJS_COMMON = $(SRCS_COMMON:.c=.o)
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCLUDES    = -I $(SRC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(HEADERS_DIR)

MLX_FLAGS   = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS_COMMON) $(OBJS_MANDATORY)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_MANDATORY) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS_COMMON) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS) 

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS_COMMON) $(OBJS_MANDATORY) $(OBJS_BONUS)
	@make -C $(LIBFT_DIR) clean
	@echo "Obje dosyaları (.o) temizlendi."

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus