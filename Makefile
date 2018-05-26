SRCLIB  =	source/mmap_allocator.c	\

SRCEX	=	source/mmap_allocator.c \
		example.c

OBJLIB	=	$(SRCLIB:.c=.o)

OBJEX	=	$(SRCEX:.c=.o)

CFLAGS	=	-Werror -Wextra -W -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -I ./include/

NAMELIB	=	mmap_allocator.a

NAMEEX 	=	example

CC	=	gcc

all:	$(NAMEEX)

$(NAMEEX):	$(OBJEX)
		$(CC) -o $(NAMEEX) $(OBJEX) $(CFLAGS)

lib:	$(OBJLIB)
	ar rc $(NAMELIB) $(OBJLIB)

clean:
	rm -f $(OBJEX) $(OBJLIB)

fclean: clean
	rm -f $(NAMEEX) $(NAMELIB)

docker:
        sudo docker run -it -v `pwd`:/home/epitest -w /home/epitest epitechcontent/epitest-docker /bin/bash

re: fclean all
