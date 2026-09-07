/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:25:08 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/30 13:31:03 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _name("Undefined"), _signed(false), _gradereqexec(150), _gradereqsign(150)
{
    std::cout << "Default Form Constructor called" << std::endl;
}

Form::Form(std::string name, bool siggned, const int gradereqsign, const int gradereqexec): _name(name), _signed(siggned),_gradereqsign(gradereqsign), _gradereqexec(gradereqexec)
{
    if (gradereqexec > 150 || gradereqsign > 150)
        throw GradeTooHighException();
    else if (gradereqsign < 1 || gradereqexec < 1)
        throw GradeTooLowException();
    std::cout << "Specified Form Constructor called" << std::endl;
}

Form::Form(const Form &copy) : _name(copy._name), _signed(copy._signed), _gradereqexec(copy._gradereqexec), _gradereqsign(copy._gradereqsign)
{
    
}

Form &Form::operator=(const Form &other)
{
    _signed = other._signed;
    return *this;
}

Form::~Form()
{
      
}

std::string Form::getName() const
{
    return _name;
}

bool Form::getSigned() const
{
    return _signed;
}

int Form::getGradeReqSign() const
{
    return _gradereqsign;
}

int Form::getGradeReqExec() const
{
    return _gradereqexec;
}

void Form::beSigned(const Bureaucrat &signer)
{
    if (signer.getGrade() <= _gradereqsign)
        _signed = true;
    else
        throw GradeTooLowException();
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Grade too high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Grade too low!");
}


std::ostream &operator<<(std::ostream &os, Form const &form)
{
    os << "Name: "<< form.getName() << " isSigned: " << form.getSigned() << " SignGrade: " << form.getGradeReqSign() << " ExecGrade: " << form.getGradeReqExec() << std::endl;
    return os;
}
