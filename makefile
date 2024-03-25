CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = cub3d
SOURCES = get_next_line.c get_next_line_utils.c main.c parcing.c
OBJECTS = $(SOURCES:.c=.o)
# LIBS =  -lmlx -framework OpenGL -framework AppKit
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)
	@echo "\033[1;32mDONE comp Cub3ddd!\033[0m"

OBJTS: $(SOURCES)
	$(CC) $(CFLAGS) -c $^

clean : 
	@echo "\033[36mCleaning Cub3ddd....\033[0m"
	@rm -rf $(OBJECTS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all