/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:47 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 11:42:38 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(): Animal()
{
    this->type = "Dog";
    std::cout << "Dog Default Constructor called" << std::endl;
}

Dog::Dog(const Dog &copy)
{
    std::cout << "Dog Copy Constructor called" << std::endl;
    *this = copy;
}

Dog::~Dog()
{
    std::cout << "Default Dog Destructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &src)
{
    std::cout << "Dog Assignation operator called" << std::endl;
    this->type = src.type;
    return *this;
}

void Dog::makeSound()const
{
    std::cout << this->getType() << " says: BarkBarkBarkBarkWOUAFWOUAFWOUAFWOUAFIMADOOOOOOOOOOOOG" << std::endl;
}
