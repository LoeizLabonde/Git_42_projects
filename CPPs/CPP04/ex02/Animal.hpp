/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:27:31 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 20:52:16 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP

# define ANIMAL_HPP

# include <string>
# include <iostream>
# include <cstdio>
# include <cstdlib>

class Animal
{
    protected:
        std::string type;
        Animal();
        
    public:
        
        Animal(const Animal &copy);
        virtual ~Animal();

        Animal &operator=(const Animal &src);

        virtual void makeSound() const;
        std::string getType() const;
};

#endif