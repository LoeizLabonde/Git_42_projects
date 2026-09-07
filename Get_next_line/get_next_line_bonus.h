/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:22 by llabonde          #+#    #+#             */
/*   Updated: 2024/06/25 13:24:56 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define MAX_FD 1024

char	*get_next_line(int fd);

char	*ft_get_read_file(int fd, char *str);
char	*ft_get_nl(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strchr(char *s, int c);

#endif