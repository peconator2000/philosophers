# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vellie <vellie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 18:29:03 by vellie            #+#    #+#              #
#    Updated: 2022/01/20 18:29:05 by vellie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ./philo/philo
NAME_BONUS = ./philo_bonus/philo_bonus
INCLUDES = ./philo/philo.h
INCLUDES_BONUS = ./philo_bonus/philo_bonus.h
SRC = ./philo/philo.c ./philo/philo_utils.c ./philo/philo_actions.c ./philo/philo_death.c ./philo/philo_init.c ./philo/philo_lib.c
SRC_BONUS = ./philo_bonus/philo_bonus.c ./philo_bonus/philo_utils_bonus.c ./philo_bonus/philo_actions_bonus.c ./philo_bonus/philo_death_bonus.c ./philo_bonus/philo_inits_bonus.c ./philo_bonus/philo_lib_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
REM = rm -rf


all: $(NAME)

$(NAME): $(INCLIDES) $(OBJ) $(SRC) Makefile
	gcc -Wall -Wextra -Werror -I $(INCLUDES) $(OBJ) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(INCLIDES_BONUS) $(OBJ_BONUS) $(SRC_BONUS) Makefile
	gcc -Wall -Wextra -Werror -I $(INCLUDES_BONUS) $(OBJ_BONUS) -o $(NAME_BONUS)


.c.o:
	gcc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

clean:
	$(REM) $(OBJ) $(OBJ_BONUS)

fclean:	clean
	$(REM) $(NAME) $(NAME_BONUS)

re:	fclean all

.PHONY: all clean fclean