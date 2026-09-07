/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 06:45:56 by llabonde          #+#    #+#             */
/*   Updated: 2025/10/16 07:45:07 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"


bool isInteger(double value)
{
    return std::floor(value) == value;
}


void printResult(double result)
{
    if (isInteger(result))
        std::cout << static_cast<int>(result) << std::endl;

    else
        std::cout << std::fixed << std::setprecision(2) << result << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " \"operant operant operator ...\"" << std::endl;
        return RETURN_FAILURE;
    }

    try
    {
        RPN rpn;
        double result = rpn.evaluate(argv[1]);
        printResult(result);
    }
    
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}
