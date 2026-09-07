/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:25:08 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 10:05:13 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : _name("Undefined"), _signed(false), _gradereqexec(150), _gradereqsign(150)
{
    std::cout << "Default Form Constructor called" << std::endl;
}

AForm::AForm(std::string name, bool siggned, const int gradereqsign, const int gradereqexec): _name(name), _signed(siggned),_gradereqsign(gradereqsign), _gradereqexec(gradereqexec)
{

}

AForm::AForm(const AForm &copy) : _name(copy._name), _signed(copy._signed), _gradereqexec(copy._gradereqexec), _gradereqsign(copy._gradereqsign)
{
    
}

AForm &AForm::operator=(const AForm &other)
{
    _signed = other._signed;
    return *this;
}

AForm::~AForm()
{
      
}

std::string AForm::getName() const
{
    return _name;
}

bool AForm::getSigned() const
{
    return _signed;
}

int AForm::getGradeReqSign() const
{
    return _gradereqsign;
}

int AForm::getGradeReqExec() const
{
    return _gradereqexec;
}

void AForm::setSigned(bool state)
{
    this->_signed = state;
}

void AForm::beSigned(const Bureaucrat &signer)
{
    if (signer.getGrade() <= _gradereqsign)
        _signed = true;
    else
        throw GradeTooLowException();
}

void AForm::execute(const Bureaucrat &executor) const
{
    if (_signed == false)
        throw IsNotSignedException();
    if (_gradereqexec < executor.getGrade())
        throw GradeTooLowException();
    
    performAction();
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}

const char *AForm::IsNotSignedException::what() const throw()
{
	return ("Form can not be executed, because it is not signed!");
}

std::ostream &operator<<(std::ostream &os, AForm const &form)
{
    os << "Name: "<< form.getName() << " isSigned: " << form.getSigned() << " SignGrade: " << form.getGradeReqSign() << " ExecGrade: " << form.getGradeReqExec() << std::endl;
    return os;
}
