NAME	= minishell
LIBFT	= libft
LIBTST	= tests
DIST	= debug

CC		= /usr/bin/gcc
DBG		= valgrind

SRCDIR	= srcs
OBJDIR	= objs/$(DIST)
INCDIR	= includes
TSTDIR	= tests

CFLAGS	= -Wall -Wextra -Werror
IFLAGS	= -I$(INCDIR) -I$(LIBFT)/includes
LFLAGS	= -L$(LIBFT) -lft -lcurses -ltermcap

LOG		= err.log

MAIN	= $(SRCDIR)/main.c

SRCS	= $(addprefix $(SRCDIR)/, 												\
			$(addprefix ft_term/, ft_term.c init.c signals.c line.c line_edit.c	\
				history.c input.c output.c prompt.c controls.c					\
				cursor_line.c cursor_hist.c selection.c clipboard.c)			\
			$(addprefix lexer/, lexer.c token.c token_types.c))

OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS) $(MAIN))
OBJDS	= $(addprefix $(OBJDIR)/, ft_term lexer)

HDRS	= $(addprefix $(INCDIR)/, ft_term.h lexer.h)

ifeq ($(DIST), debug)
	CFLAGS += -g -DDIST_DEBUG
	NAME := $(NAME)-debug
endif

all:			libft $(NAME)

debug:			all
	@echo DBG $(NAME)
	@$(DBG) ./$(NAME) 2>$(LOG)

log:
	tail -f $(LOG) 2>&1 | perl -ne 'if (/file truncated/) {system 'clear'; print} else {print}'

libft:
	make -C $(LIBFT) libft.a CC="$(CC)" CFLAGS="$(CFLAGS)"

libtest:
	make -C $(LIBTST) libtest.a CC="$(CC)" CFLAGS="$(CFLAGS)"

$(LIBFT)/libft.a: libft
$(LIBTST)/libtest.a: libtest

$(OBJDS):
	@echo MK $@
	mkdir -p $@

$(NAME):		$(OBJDS) $(OBJS) $(LIBFT)/libft.a
	@echo LINK $(NAME)
	$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $(NAME)

test:			NAME := $(NAME)-test
test:			LFLAGS += -Ltests -ltest
test:			MAIN =
test:			libtest $(NAME)
	./$(NAME)

$(OBJDIR):
	@echo MK $@
	mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HDRS) Makefile
	@echo CC $<
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	make -C $(LIBFT) $@
	make -C $(LIBTST) $@
	/bin/rm -rf $(OBJDIR)

fclean:			clean
	make -C $(LIBFT) $@
	make -C $(LIBTST) $@
	@echo RM $(NAME)
	@echo RM $(NAME)-test
	/bin/rm -f $(NAME) $(NAME)-test
	@echo RM test.dSYM
	/bin/rm -rf test.dSYM

re:				fclean all

test-dir:		$(OBJDIR)
	@echo MK $(OBJDIR)/tests
	mkdir -p $(OBJDIR)/tests

.PHONY: libft libtest clean fclean

$(VERBOSE).SILENT:
