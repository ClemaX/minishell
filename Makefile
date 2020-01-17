NAME	= minishell
LIBFT	= libft
CC		= /usr/bin/gcc
SRCDIR	= srcs
OBJDIR	= objs
INCDIR	= includes
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I$(INCDIR) -I$(LIBFT)/includes
LFLAGS	= -L$(LIBFT) -lft
MAIN	= $(SRCDIR)/minishell.c
SRCS	= $(addprefix $(SRCDIR)/,												\
				line.c minish_cmd.c												\
	$(addprefix builtins/ft_, cd.c echo.c exit.c pwd.c env.c unset.c export.c)	\
	$(addprefix command/, arguments.c meta.c arg_utils.c command.c)				\
	$(addprefix env/, path.c)													\
	$(addprefix map/, map.c map_utils.c map_sort.c))
OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS) $(MAIN))
OBJDS	= $(addprefix $(OBJDIR)/, builtins command env map)
HDRS	= $(addprefix $(INCDIR)/, builtins.h command.h env.h line.h map.h)
TESTS	= $(addprefix tests/, main.c map_test.c path_test.c)

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

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HDRS) Makefile
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	make -C $(LIBFT) $@
	/bin/rm -rf $(OBJDIR)

fclean: 		clean
	make -C $(LIBFT) $@
	/bin/rm -f $(NAME)

re:				fclean all

test-dir:		$(OBJDIR)
	mkdir -p $(OBJDIR)/tests

test:			SRCS	+=	$(TESTS)
test:			OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
test:			CFLAGS	+=	-g
test:			test-dir re

.PHONY: libft clean fclean
