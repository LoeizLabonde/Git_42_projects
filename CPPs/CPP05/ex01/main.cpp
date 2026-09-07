/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:33:16 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/30 14:20:28 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	std::cout << "TESTING CONSTRUCTOR" << std::endl;
	std::cout << "TEST 1" << std::endl;	
	try
	{
		Form ONE("One", false, 50, 50);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << '\n';
	}
	std::cout << "TEST 2" << std::endl;	
	try
	{
		Form TWO("two", false, -75, 75);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << '\n';
	}
	std::cout << "TEST 3" << std::endl;	
	try
	{
		Form THREE("three", false, 200, 75);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << '\n';
	}
	std::cout << "TEST 4" << std::endl;		
	try
	{
		Form FOUR("four", false, 75, 275);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << '\n';
	}
		std::cout << "TEST 4.5" << std::endl;		
	try
	{
		Form FOURA("foura", false, 75, -2);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << '\n';
	}
	std::cout << "TESTING Methods" << std::endl;	
	std::cout << "TEST 5" << std::endl;	
	Form FIVE("five", false, 75, 75);
	Bureaucrat SIX("six", 74);
	Form SEVEN("seven", false, 73, 73);

	try
	{
		SIX.signForm(FIVE);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " <<  e.what() << '\n';
	}
	std::cout << "TEST 6" << std::endl;	
	try
	{
		SIX.signForm(SEVEN);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " <<  e.what() << '\n';
	}
	std::cout << FIVE;
	std::cout << SIX;
	std::cout << SEVEN;
	

	
	
	
    return 0;
}