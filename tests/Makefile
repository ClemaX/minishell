NAME	=		libtest.a
SRCDIR	=		srcs
INCDIR	=		includes
OBJDIR	=		objs
CC		=		/usr/bin/clang
AR		=		/usr/bin/ar
RM		=		/bin/rm
AFLAGS	=		rcus
CFLAGS	=		-Wall -Wextra -Werror
IFLAGS	=		-I$(INCDIR)
HEADRS	=		$(addprefix $(INCDIR)/, diff.h tests.h units.h)

SRCS	=		$(addprefix $(SRCDIR)/,										\
			$(addprefix diff/diff_, bool.c sizes.c types.c)					\
			$(addprefix units/,												\
				$(addprefix clipboard/, copy.c cut.c paste.c)				\
			)																\
			main.c rand_term.c rand.c lst.c run.c)

OBJDS	=		$(addprefix $(OBJDIR)/,	diff $(addprefix units/, clipboard))

OBJS	=		$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all:			$(NAME)

$(NAME):		$(OBJDS) $(OBJS)
	@echo AR $(NAME)
	@$(AR) $(AFLAGS) $@ $(OBJS)

$(OBJDS):
		mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(INCDIR)/$(HEADER) Makefile
	@echo CC $<
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	@echo RM $(OBJDIR)
	@$(RM) -rf $(OBJDIR)

fclean:			clean
	@echo RM $(NAME)
	@$(RM) -f $(NAME)

re:				fclean all

.PHONY	=		all clean fclean re
