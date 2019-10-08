##
## TABIS PROJECT, 2019
## Makefile
## File description:
## All purpose C++ compilation Makefile by Tabis Lucas
##

OBJ_COLOR=      	\033[0;36m
COM_COLOR=      	\033[0;34m
NO_COLOR=       	\033[m
OK=     		"[OK]"


SRC_DIR=        	$(realpath src)

SRC=			$(wildcard $(SRC_DIR)/*.cpp)
OBJ=			$(SRC:.cpp=.o)

CPPFLAGS=		-Iinclude -LLib/src -lapcpplib -g -W -Wall -Wextra -Werror

NAME=			project_name


all:		library_comp src_comp

library_comp:
			cd Lib/src && $(MAKE)

src_comp:	$(OBJ)
			g++ -o $(NAME) $(OBJ) $(CPPFLAGS)
			@echo -e "$(OK_COLOR)"$(OK) "$(COM_COLOR)""Compilation finished !" "$(NO_COLOR)"

tests_run:
			cd tests/ && $(MAKE)

clean:
			@$(RM) -f $(OBJ)
			@find -type f -name '*~' -delete
			@find -type f -name '#*#' -delete
			@find -type f -name '*.o' -delete
			@find -type f -name '*.gcda' -delete
			@find -type f -name '*.gcno' -delete
			@$(RM) -r -f *~ \#*\#

fclean:		clean
			cd tests/ && $(MAKE) fclean
			@$(RM) -f $(NAME)

re:		fclean all

.PHONY:		tests_run clean fclean re src_comp library_comp
