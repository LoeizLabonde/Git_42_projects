/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:12:38 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 13:34:12 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <ostream>
# include <exception>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
    private:
        const std::string _name;
        bool _signed;
        const int _gradereqsign;
        const int _gradereqexec;
        virtual void performAction() const  = 0;
        
    public:
        AForm();
        AForm(const std::string _name, bool siggned, const  int gradereqsign, const int gradereqexec);
        AForm(const AForm &copy);
        AForm &operator=(const AForm &other);
        ~AForm();

        std::string getName() const;
        bool getSigned() const;
        int getGradeReqSign() const;
        int getGradeReqExec() const;
        void setSigned(bool state);

        void beSigned(const Bureaucrat &signer);
        void execute(const Bureaucrat &executor) const;
        
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

        class IsNotSignedException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};

std::ostream &operator<<(std::ostream & os, AForm const &other);

#endif
