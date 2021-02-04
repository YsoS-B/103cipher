##
## EPITECH PROJECT, 2020
## makefile
## File description:
## makefile
##

SRC	=	$(shell find -name "*.c")

OBJ	=	$(SRC:.c=.o)

NAME	=	103cipher

all:	$(NAME)

$(NAME):	$(OBJ)
		@gcc -o $(NAME) $(SRC) -lm
		@echo "Compilation en cours ..."
		@echo "Compilation réussie."
		@echo "La bibliothèque est prête à être utlisée."

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	find -name "*~" -delete
	find -name "*#" -delete
	find -name "*.o" -delete

re:	fclean all
