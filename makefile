NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Dizinler
SRC_DIR     = src
MLX_DIR     = include/minilibx-linux

# Kaynak Dosyalar
# Projeye yeni .c dosyaları ekledikçe buraya alt alta ekleyebilirsin
SRCS        = $(SRC_DIR)/main.c
OBJS        = $(SRCS:.c=.o)

# Include ve Kütüphane Bayrakları
# Header (.h) dosyaları src içinde olduğu için -I $(SRC_DIR) ile orası da gösterildi
INCLUDES    = -I $(SRC_DIR) -I $(MLX_DIR)

# MLX Linkleme Bayrakları (Linux/X11 bağımlılıkları dahil)
MLX_FLAGS   = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Temel Kurallar
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Derleniyor: $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "Başarılı: $(NAME) hazır!"

# .c dosyalarını .o dosyalarına çevirme kuralı
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