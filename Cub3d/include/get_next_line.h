/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:36:43 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/10 14:13:33 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifdef MAX_FD
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft.h"

# define MAX_FD 1048576

char	*get_next_line(int fd);

char	*f_strchr(char *s, int c);
char	*f_strdup(char *s1);
char	*f_strjoin(char *s1, char *s2);

#endif
