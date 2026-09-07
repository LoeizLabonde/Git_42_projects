/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:49:27 by llabonde          #+#    #+#             */
/*   Updated: 2024/06/28 11:29:08 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_printchar(va_arg(args, int));
	else if (format == 's')
		print_length += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		print_length += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		print_length += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		print_length += ft_printpercent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_length += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			print_length += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}

/*
int	main(void)
{
	long heure = 12345678901112;
	unsigned int heure2 = -620;
	
	char c ='c'; 
	char *str = "l'heure de t'acheter une montre mdr.";
	ft_putstr_fd("Bonsoir\n\nDEBUT DES TEST\n", 1);
	ft_printf("ABC\n");
	ft_printf("Il est deja %% heure!!\n");
	ft_printf("Hein? Il est %c heure mdr...\n", c);
	ft_printf("Je crois que c'est %s\n", str);
 	ft_printf("Super, %d plutot? Ou bien %i?\n", heure, heure2);
	ft_printf("Peut etre %p?\n", heure);
	printf("Peut etre %p?\n", (void *)heure);
	ft_printf("Peut etre %p?\n", 0);
	printf("Peut etre %p?\n", (void*)0);
	ft_printf("little x : %x ou big X : %X?\n", heure2, heure2);
	printf("little x : %x ou big X : %X?\n", heure2, heure2);
	ft_printf("Je ne sais plus...");
	ft_putstr_fd("\nFIN DES TEST\n", 1);
}
*/