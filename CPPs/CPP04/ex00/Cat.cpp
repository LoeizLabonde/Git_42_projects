/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:42 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 13:41:16 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(): Animal()
{
    this->type = "Cat";
    std::cout << "Cat Default Constructor called" << std::endl;
}

Cat::Cat(const Cat &copy)
{
    std::cout << "Cat Copy Constructor called" << std::endl;
    *this = copy;
}

Cat::~Cat()
{
    std::cout << "Default Cat Destructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &src)
{
    std::cout << "Cat Assignation operator called" << std::endl;
    this->type = src.type;
    return *this;
}

void Cat::makeSound()const
{    
    std::cout << this->getType() << " says: MEOWMEOWIMACAAAAAAAAAAAAAAAAAAT" << std::endl;
}