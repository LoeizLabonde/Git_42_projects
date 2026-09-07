/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:57:39 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 13:56:21 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal()
{
    this->type = "WrongCat";
    std::cout << "WrongCat Default Constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &copy)
{
    std::cout << "WrongCat Copy Constructor called" << std::endl;
    *this = copy;
}

WrongCat::~WrongCat()
{
    std::cout << "Default WrongCat Destructor called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &src)
{
    std::cout << "WrongCat Assignation operator called" << std::endl;
    this->type = src.type;
    return *this;
}

void WrongCat::makeSound()const
{
    std::cout << this->getType() << " says: SkibidibapImNotSupposedToMeow" << std::endl;
}

