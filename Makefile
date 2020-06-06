NAME	= minishell
LIBFT	= libft
CC		= /usr/bin/gcc
SRCDIR	= srcs
OBJDIR	= objs
INCDIR	= includes
CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I$(INCDIR) -I$(LIBFT)/includes
LFLAGS	= -L$(LIBFT) -lft -lcurses -ltermcap
MAIN	= $(SRCDIR)/main.c
SRCS	= $(addprefix $(SRCDIR)/, 												\
			$(addprefix ft_term/, ft_term.c init.c signals.c history.c input.c	\
				output.c controls.c cursor.c line.c selection.c)				\
			$(addprefix lexer/, lexer.c token_types.c))
OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS) $(MAIN))
OBJDS	= $(addprefix $(OBJDIR)/, ft_term lexer)
HDRS	= $(addprefix $(INCDIR)/, ft_term.h lexer.h)

TESTSD	= tests/srcs/
TESTID	= tests/includes/
TESTS	= $(addprefix $(TESTSD), main.c error.c test_utils.c value_utils.c		\
			map_test.c path_test.c prompt_test.c lexer_test.c line_tests.c		\
			tab_utils.c)

all:			libft $(NAME)

libft:
	make -C $(LIBFT) libft.a CC=$(CC)

$(LIBFT)/libft.a: libft

$(OBJDS):
	@echo MK $@
	mkdir -p $@

$(NAME):		$(OBJDS) $(OBJS) $(LIBFT)/libft.a
	@echo LINK $(NAME)
	$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $(NAME)

$(OBJDIR):
	@echo MK $@
	mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HDRS) Makefile
	@echo CC $<
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	make -C $(LIBFT) $@
	/bin/rm -rf $(OBJDIR)

fclean: 		clean
	make -C $(LIBFT) $@
	@echo RM $(NAME) test
	/bin/rm -f $(NAME) test
	@echo RM test.dSYM
	/bin/rm -rf test.dSYM

re:				fclean all

test-dir:		$(OBJDIR)
	@echo MK $(OBJDIR)/tests
	mkdir -p $(OBJDIR)/tests

test:			IFLAGS	+=	-I$(TESTID)
test: 			HDRS	+=	$(addprefix $(TESTID), test.h)
test:			SRCS	+=	$(TESTS)
test:			OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
test:			CFLAGS	=	-Wall -Wextra -g
test:			NAME	=	test
test:			test-dir re
	./$(NAME)

.PHONY: libft clean fclean

$(VERBOSE).SILENT:
