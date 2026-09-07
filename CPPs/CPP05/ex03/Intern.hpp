/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:54:12 by llabonde          #+#    #+#             */
/*   Updated: 2025/07/02 14:09:31 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>
# include "AForm.hpp"
# include "Bureaucrat.hpp"
# include <iostream>
# include <exception>

class Intern
{
    private :
    
    public :
        Intern();
        Intern(const Intern &copy);
        Intern &operator=(const Intern &other);
        ~Intern();

        AForm *makeForm(const std::string formName, const std::string formTarget);
    
};

#endif