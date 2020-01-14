NAME	= minishell
LIBFT	= libft
CC		= /usr/bin/gcc
SRCDIR	= srcs
OBJDIR	= objs
INCDIR	= includes
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I$(INCDIR) -I$(LIBFT)/includes
LFLAGS	= -L$(LIBFT) -lft
SRCS	= $(addprefix $(SRCDIR)/,							\
	command.c line.c minishell.c							\
	$(addprefix builtins/ft_, cd.c echo.c exit.c pwd.c))
OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
HDRS	= $(addprefix $(INCDIR)/, command.h line.h)

all:			libft $(NAME)

libft:
	make -C $(LIBFT) libft.a

$(LIBFT)/libft.a: libft

$(NAME):		$(OBJDIR) $(OBJS) $(LIBFT)/libft.a
	$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRS) Makefile
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	make -C $(LIBFT) $@
	/bin/rm -rf $(OBJDIR)

fclean: 		clean
	make -C $(LIBFT) $@
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: libft clean fclean
