/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:44 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 11:41:25 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include <iostream>
#include "Animal.hpp"

class Dog : public Animal
{
    public:
            Dog();
            Dog(const Dog &copy);
            ~Dog();
            Dog &operator=(const Dog &src);
            void makeSound() const;

    private:
    
};

#endif