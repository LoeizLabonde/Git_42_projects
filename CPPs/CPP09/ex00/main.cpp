/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 05:54:28 by llabonde          #+#    #+#             */
/*   Updated: 2025/10/16 07:44:59 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{

    if (argc != EXPECTED_ARGC)
    {
        std::cerr << NC << RED_BG << "Usage: ./btc input.txt" << NC << std::endl;
        return RETURN_FAILURE;
    }
    try
    {
        BitcoinExchange exchange;
        exchange.loadDatabase("data.csv");
        exchange.processInput(argv[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << NC << RED_BG << e.what() << NC << std::endl;
        return RETURN_FAILURE;
    }
    return RETURN_SUCCESS;
}

