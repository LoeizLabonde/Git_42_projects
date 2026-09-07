/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:13:43 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 11:44:02 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(): type("Undefined")
{
    std::cout << "Animal Default Constructor called" << std::endl;
}

Animal::Animal(const Animal &copy)
{
    std::cout << "Animal Copy Constructor called" << std::endl;
    *this = copy;
}

Animal::~Animal()
{
    std::cout << "Default Animal Destructor called" << std::endl;
}

Animal &Animal::operator=(const Animal &src)
{
    std::cout << "Animal Assignation operator called" << std::endl;
    this->type = src.type;
    return *this;
}

void Animal::makeSound()const
{
    std::cout << "Bruh..." << std::endl;
}

std::string Animal::getType()const
{
     return (this->type);
}
