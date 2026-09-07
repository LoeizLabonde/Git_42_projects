/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:54:15 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 14:09:39 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
    
}

Intern::Intern(const Intern &other)
{
    
}

Intern &Intern::operator=(const Intern &other)
{
    return (*this);
}

Intern::~Intern()
{
    
}

AForm *Intern::makeForm(const std::string formname, const std::string formTarget)
{
    int i = 0;
    std::string available_forms[] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
    
    while (i < 3 && formname != available_forms[i])
        i++;

    switch(i)
    {
        case 0:
            std::cout << "Intern creates " << formname << std::endl;
            return (new ShrubberyCreationForm(formTarget));
        case 1:
            std::cout << "Intern creates " << formname << std::endl;
            return (new RobotomyRequestForm(formTarget));
        case 2:
            std::cout << "Intern creates " << formname << std::endl;
            return (new PresidentialPardonForm(formTarget));
        default :
            std::cout << "Form doesn't exist." << std::endl;
            return (NULL);
    }
}