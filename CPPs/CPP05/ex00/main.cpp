/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:33:16 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/30 10:55:28 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
//Constructor Test
std::cout << "-TEST ONE TWO-" <<std::endl;
std::cout << "-test ONE-" <<std::endl;
    try
	{
		Bureaucrat ONE("One", 1500);
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
std::cout << "-test TWO-" <<std::endl;
    try
	{
		Bureaucrat TWO("two", -10);
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
    
//Incre & Decre Test
//Increment
std::cout << "-TEST THREE FOUR-" <<std::endl;
std::cout << "-test THREE-" <<std::endl;
    Bureaucrat THREE("three", 2);
    try
	{
		THREE.incrGrade();
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
    std::cout << THREE;

    try
	{
		THREE.incrGrade();
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
    std::cout << THREE;
    
//Decrement
std::cout << "-test FOUR-" <<std::endl;
    Bureaucrat FOUR("Four", 149);
    try
	{
		FOUR.decrGrade();
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
    std::cout << FOUR;

    try
	{
		FOUR.decrGrade();
	}
	catch(const std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
    std::cout << FOUR;
    

    return 0;
}