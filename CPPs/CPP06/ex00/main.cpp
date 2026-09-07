/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:42:20 by llabonde          #+#    #+#             */
/*   Updated: 2025/08/29 09:37:08 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int ac, char **argv)
{
    if (ac != 2)
    {
        std::cout << "Please enter char/ int/ float/ double value" << std::endl;
        return 0;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}
