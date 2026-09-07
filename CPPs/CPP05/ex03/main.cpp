/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:33:16 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 14:18:05 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int main(void)
{

	srand(time(NULL));

	std::cout << "-TESTING EX02-" << std::endl;

	Bureaucrat ONE("One", 130);//can only do shrub
	Bureaucrat TWO("Two", 30);//can do shrub and Robo
	Bureaucrat THREE("Three", 5);//can do all of them
	
	ShrubberyCreationForm SCF("Shrub");
	PresidentialPardonForm PPF("Presi");
	RobotomyRequestForm RRF("Robot");

	std::cout << "-SHRUBBY-" << std::endl;
	ONE.executeForm(SCF);
	ONE.signForm(SCF);
	ONE.executeForm(SCF);
	ONE.signForm(PPF);
	ONE.signForm(RRF);

	std::cout << "-ROBOTOMY-" << std::endl;
	TWO.executeForm(RRF);
	TWO.signForm(RRF);
	TWO.executeForm(RRF);
	TWO.signForm(PPF);
	TWO.signForm(SCF);
	
	std::cout << "-PRESIDENTIAL PARDON-" << std::endl;
	THREE.executeForm(PPF);
	THREE.signForm(PPF);
	THREE.executeForm(PPF);
	THREE.signForm(SCF);
	THREE.signForm(RRF);
	
	std::cout << "-END TESTING EX02-" << std::endl;
	std::cout << "-TESTING EX03-" << std::endl;
	
	Intern Tommy;
	AForm *roboIntern;
	AForm *presIntern;
	AForm *shrubIntern;

	roboIntern = Tommy.makeForm("StrangeForm", "weird");
	roboIntern = Tommy.makeForm("RobotomyRequestForm", "Here");
	presIntern = Tommy.makeForm("PresidentialPardonForm", "Here");
	shrubIntern = Tommy.makeForm("ShrubberyCreationForm", "Here");
	std::cout << roboIntern->getName() << std::endl;
	std::cout << presIntern->getName() << std::endl;
	std::cout << shrubIntern->getName() << std::endl;

	delete roboIntern;
	delete presIntern;
	delete shrubIntern;
    return 0;
}