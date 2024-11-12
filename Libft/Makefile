NAME = libft.a

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar
ARFLAGS	= -rcs
RM	= rm
RMFLAGS = -f
OBJDIR = obj

# Define color codes
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
COLOUR_RESET=\033[0m

.SILENT:

SRC	= $(wildcard *.c)
OBJ 	= $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRC)))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(COLOUR_GREEN)=>Linking objects...$(COLOUR_RESET)"
	$(AR) $(ARFLAGS) $@ $(OBJ)

$(OBJDIR)/%.o: %.c
	@echo "$(COLOUR_BLUE)=>Compiling Libft library...$(COLOUR_RESET)"
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o$@ -c $<
clean:
	@echo "$(COLOUR_YELLOW)=> Cleaning Libft library...$(COLOUR_RESET)"
	$(RM) $(RMFLAGS) $(OBJ)

fclean: clean
	@echo "$(COLOUR_YELLOW)=> Cleaning Libft library...$(COLOUR_RESET)"

	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
