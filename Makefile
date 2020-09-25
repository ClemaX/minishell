NAME	= minishell
LIBFT	= libft
LIBTST	= tests
DIST	= debug

CC		= /usr/bin/gcc
DBG		= valgrind
RM		= /bin/rm

SRCDIR	= srcs
BLDDIR	= objs
OBJDIR	= $(BLDDIR)/$(DIST)
INCDIR	= includes
TSTDIR	= tests

CFLAGS	= -Wall -Wextra -Werror -g3# -fsanitize=address
IFLAGS	= -I$(INCDIR) -I$(LIBFT)/includes
LFLAGS	= -L$(LIBFT) -lft -lcurses -ltermcap

LOG		= err.log

MAIN	= $(SRCDIR)/main.c

SRCS	= $(addprefix $(SRCDIR)/, 												\
			$(addprefix lexer/, lexer.c token.c token_types.c token_utils.c)	\
			$(addprefix abstract_dict/, exe_cmd.c exe_redirection.c				\
				execute_abstract_dict.c free_abstract_dict.c					\
				gen_abstract_dict.c)											\
			$(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c		\
				unset.c)														\
			$(addprefix operators/, pipes.c redirections.c)						\
		)

OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS) $(MAIN))
OBJDS	= $(addprefix $(OBJDIR)/, lexer abstract_dict builtins operators)

HDRS	= $(addprefix $(INCDIR)/, lexer.h)

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
test:			libtest $(OBJDS) $(OBJS) $(LIBFT)/libft.a
	@echo LINK $(NAME)
	$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $(NAME)
	./$(NAME) 2>$(LOG)

$(OBJDIR):
	@echo MK $@
	@mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HDRS) Makefile
	@echo CC $<
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	make -C $(LIBFT) $@
	make -C $(LIBTST) $@
	@echo RM $(BLDDIR)
	@$(RM) -rf $(BLDDIR)

fclean:			clean
	make -C $(LIBFT) $@
	make -C $(LIBTST) $@
	@echo RM $(NAME)
	@echo RM $(NAME)-test
	@$(RM) -f $(NAME) $(NAME)-test
	@echo RM test.dSYM
	@$(RM) -rf test.dSYM

re:				fclean all

test-dir:		$(OBJDIR)
	@echo MK $(OBJDIR)/tests
	@mkdir -p $(OBJDIR)/tests

.PHONY: libft libtest clean fclean

$(VERBOSE).SILENT:
