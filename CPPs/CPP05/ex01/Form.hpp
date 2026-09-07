/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:12:38 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/30 14:15:00 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FROM_HPP

# include <string>
# include <ostream>
# include <exception>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
    private:
        const std::string _name;
        bool _signed;
        const int _gradereqsign;
        const int _gradereqexec;
        
    public:
        Form();
        Form(const std::string _name, bool siggned, const  int gradereqsign, const int gradereqexec);
        Form(const Form &copy);
        Form &operator=(const Form &other);
        ~Form();

        std::string getName() const;
        bool getSigned() const;
        int getGradeReqSign() const;
        int getGradeReqExec() const;

        void beSigned(const Bureaucrat &signer);
        
        class GradeTooHighException : public std::exception
        {
            public :
                virtual const char *what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
    
};

std::ostream &operator<<(std::ostream & os, Form const &other);

#endif
