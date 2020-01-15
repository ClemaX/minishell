NAME	= minishell
LIBFT	= libft
CC		= /usr/bin/gcc
SRCDIR	= srcs
OBJDIR	= objs
INCDIR	= includes
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I$(INCDIR) -I$(LIBFT)/includes
LFLAGS	= -L$(LIBFT) -lft
SRCS	= $(addprefix $(SRCDIR)/,												\
	command.c line.c minishell.c minish_cmd.c									\
	$(addprefix args/, arguments.c arg_utils.c)									\
	$(addprefix builtins/ft_, cd.c echo.c exit.c pwd.c env.c unset.c export.c)	\
	$(addprefix map/, map.c map_utils.c map_sort.c))
OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJDS	= $(addprefix $(OBJDIR)/, args builtins map)
HDRS	= $(addprefix $(INCDIR)/, builtins.h command.h line.h map.h)

all:			libft $(NAME)

libft:
	make -C $(LIBFT) libft.a

$(LIBFT)/libft.a: libft

$(OBJDS):
		mkdir -p $@

$(NAME):		$(OBJDS) $(OBJS) $(LIBFT)/libft.a
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
