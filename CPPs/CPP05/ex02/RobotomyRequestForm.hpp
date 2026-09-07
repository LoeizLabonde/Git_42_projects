/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 09:36:17 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 13:26:39 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include <string>
# include "AForm.hpp"
# include <stdlib.h>
# include <time.h>

class RobotomyRequestForm : public AForm
{
    private :
        std::string _target;
        virtual void performAction() const;
    
    public :
        RobotomyRequestForm();
        RobotomyRequestForm(std::string target);
        RobotomyRequestForm(const RobotomyRequestForm &copy);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
        ~RobotomyRequestForm();

        std::string getTarget();

        class RobotizationFailed : public std::exception
        {
            public :
                virtual const char *what() const throw();
        };

};

#endif