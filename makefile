NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -D_GNU_SOURCE

SRC_DIR     = src
MLX_DIR     = include/minilibx-linux
LIBFT_DIR   = include/libft
HEADERS_DIR = include

SRCS        = $(SRC_DIR)/main.c \
			  $(SRC_DIR)/render.c \
              $(SRC_DIR)/n1.c \
              $(SRC_DIR)/n2.c \
              $(SRC_DIR)/n3.c \
              $(SRC_DIR)/n4.c \
              $(SRC_DIR)/n5.c \
              $(SRC_DIR)/zget_next_line.c \
			  $(SRC_DIR)/free_game.c \
			  $(SRC_DIR)/dda.c \
			  $(SRC_DIR)/texture.c \
			  $(SRC_DIR)/draw_map.c \
              $(wildcard $(LIBFT_DIR)/*.c)
OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I $(SRC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(HEADERS_DIR)

MLX_FLAGS   = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Derleniyor: $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "Başarılı: $(NAME) hazır!"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Obje dosyaları (.o) temizlendi."

fclean: clean
	@rm -f $(NAME)
	@echo "Çalıştırılabilir dosya ($(NAME)) silindi."

re: fclean all

.PHONY: all clean fclean re