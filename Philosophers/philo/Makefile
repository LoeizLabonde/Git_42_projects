# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:42:36 by llabonde          #+#    #+#              #
#    Updated: 2024/10/07 10:16:14 by llabonde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = philo

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

# Liste des fichiers source
SRCS = main.c \
       init.c \
       threads.c \
       monitor.c \
       routines_actions.c \
       utils.c

# Dossier des fichiers objets
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

# Règle par défaut (compilation)
all: $(NAME)

# Créer l'exécutable
$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Créer le dossier obj
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compilation des fichiers objets dans obj/
$(OBJDIR)/%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -rf $(OBJDIR)

# Nettoyage complet (fichiers objets et exécutable)
fclean: clean
	rm -f $(NAME)

# Recompilation complète
re: fclean all

# Phony targets pour éviter les conflits avec des fichiers du même nom
.PHONY: all clean fclean re
