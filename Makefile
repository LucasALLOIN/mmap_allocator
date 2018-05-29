ROOT	=	.

SRC_DIR	=	sources

CC	=	gcc

NAME	=	example

REAL	=	$(ROOT)/build

LIB	=	liballocator.a

SRC	=	$(SRC_DIR)/mmap_allocator.c \
		$(SRC_DIR)/mmap_utils.c \
		$(SRC_DIR)/mmap_calloc.c \
		$(SRC_DIR)/mmap_init.c \
		$(SRC_DIR)/mmap_free.c

SRC_BIN	=	$(SRC_DIR)/example.c

WARN	=	-W -Wall -Wextra

CFLAGS	=	-I $(ROOT)/includes $(WARN) -g

LDFLAGS	=	

LIB	?=	1

TEST	?=	0

DEB	?=      0

G	=	-g

V	?=	@

OBJS	=	$(patsubst $(SRC_DIR)/%.c, $(REAL)/%.o, $(SRC))

#COLOR

GREEN	=		\e[1;32m

WHITE	=		\e[1;3\e[0m

ORANGE	=		\e[1;3\e[1;33m

RED	=		\e[1;3\e[1;35m

BLUE	=		\e[1;3\e[1;34m

debug:			CFLAGS	+= $(G)

all:			$(LIB)

$(LIB):			$(OBJS)
			$(V)printf "$(GREEN)Compile sources.$(WHITE)\n"
			$(V)ar rc -o $(LIB) $(OBJS)
			$(V)printf "$(GREEN)Linking obj and Libraries.$(WHITE)\n"

$(NAME):		$(LIB)
			$(V)$(CC) -o $(REAL)/example.o -c $(SRC_DIR)/example.c $(CFLAGS)
			$(V)$(CC) -o $@ $(OBJS) $(REAL)/example.o $(CFLAGS) -L . -l allocator
			$(V)printf "$(GREEN)Dup $(NAME) into root directory.$(WHITE)\n"

debug:			fclean echo_d $(NAME)

$(REAL)/%.o:		$(SRC_DIR)/%.c
			$(V)mkdir -p $(dir $@)
			$(V)printf "$(BLUE)Compiling [$(GREEN)$(notdir $<)$(BLUE) -> $(RED)$(notdir $@)$(BLUE)]\n$(WHITE)"
			$(V)$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
			$(V)rm -rf $(OBJS)
			$(V)rm -rf $(REAL)/example.o
			$(V)printf "$(ORANGE)Removing object files.$(WHITE)\n"

fclean:			clean
			$(V)rm -f $(LIB)
			$(V)rm -f $(REAL)/$(NAME)
			$(V)rm -f $(ROOT)/$(NAME)
			$(V)printf "$(ORANGE)Removing binary file.$(WHITE)\n"

re:			fclean
			$(V)make --no-print-directory all

echo_build:
			$(V)printf "$(GREEN)Begin of the build !\n$(ORANGE)Warnings : \n$(WHITE)"

echo_d:
			$(V)printf "$(RED)DEBUG MODE initialized.$(WHITE)\n";

.PHONY: clean fclean debug all re echo_debug buildrepo
