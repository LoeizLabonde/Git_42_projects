/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:36:20 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 10:46:19 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm",false ,145, 137), _target("Undefined")
{
    
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm",false ,145, 137), _target(target)
{
    
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &copy) : AForm(copy)
{
    *this = copy;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
    _target = other._target;
    setSigned(other.getSigned());
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    
}

std::string ShrubberyCreationForm::getTarget() 
{
    return  _target;
}

void ShrubberyCreationForm::performAction() const
{
    std::ofstream outFile((_target + std::string("_shrubbery")).c_str());

    if (outFile)
    {
 		outFile << "    /\\    \n";
		outFile << "   /  \\   \n";
		outFile << "  /    \\  \n";
		outFile << " /      \\ \n";
		outFile << "/________\\\n";
		outFile << "    ||    \n";
		outFile << "    ||    \n";
		outFile << "    ||    \n";

		outFile.close();       
    }
    else 
        throw ShrubberyCreationForm::OpenFileException();
}

const char *ShrubberyCreationForm::OpenFileException::what() const throw()
{
    return ("Could not open and write te file!");
}