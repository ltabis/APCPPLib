##
## TABIS PROJECT
## Makefile
## File description:
## Makefile to compile the APCPPLib
##

SRC=           	$(wildcard *.cpp)
OBJ=            $(SRC:.cpp=.o)

CPPFLAGS=       -I../../include

NAME=           libapcpplib.a

all:           	library_comp

library_comp:   $(OBJ)
		ar rc $(NAME) $(OBJ)

clean:
		@rm -f $(OBJ)

fclean:         clean
		rm -f $(NAME)

re:             fclean all
