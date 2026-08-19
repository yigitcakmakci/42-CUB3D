NAME        = cub3D
NAME_BONUS	= cub3D_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -D_GNU_SOURCE

SRC_DIR     = src
MLX_DIR     = include/minilibx-linux
LIBFT_DIR   = include/libft
HEADERS_DIR = include

SRCS_COMMON = $(SRC_DIR)/main.c \
              $(SRC_DIR)/n1.c \
              $(SRC_DIR)/n2.c \
              $(SRC_DIR)/n3.c \
              $(SRC_DIR)/n4.c \
              $(SRC_DIR)/n5.c \
              $(SRC_DIR)/zget_next_line.c \
			  $(SRC_DIR)/free_game.c \
			  $(SRC_DIR)/dda.c \
			  $(SRC_DIR)/dda_init.c \
			  $(SRC_DIR)/player.c \
			  $(SRC_DIR)/events.c \
			  $(SRC_DIR)/player_update.c \
			  $(SRC_DIR)/texture_init.c \
			  $(SRC_DIR)/texture_draw.c \
              $(wildcard $(LIBFT_DIR)/*.c)

SRCS_MANDATORY = $(SRC_DIR)/render.c
SRCS_BONUS = $(SRC_DIR)/render_bonus.c \
			 $(SRC_DIR)/minimap_bonus.c

OBJS_COMMON = $(SRCS_COMMON:.c=.o)
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCLUDES    = -I $(SRC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(HEADERS_DIR)

MLX_FLAGS   = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS_COMMON) $(OBJS_MANDATORY)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_MANDATORY) $(MLX_FLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_COMMON) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_BONUS) -o $(NAME_BONUS) $(MLX_FLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS_COMMON) $(OBJS_MANDATORY) $(OBJS_BONUS) 
	@echo "Obje dosyaları (.o) temizlendi."

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus