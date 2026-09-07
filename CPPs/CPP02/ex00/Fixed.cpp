/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:20 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/19 11:22:36 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int  Fixed::_frac = 8;

Fixed::Fixed(void): _value(0)
{
    std::cout << "Fixed object created with default constructor" << std::endl;
}

Fixed::~Fixed(void)
{
    std::cout << "Fixed object destroyed" << std::endl;
}

Fixed::Fixed(Fixed const & copy)
{
    std::cout << "Fixed object copied" << std::endl;
    *this = copy;
}

Fixed   &Fixed::operator=(const Fixed & copy)
{
    std::cout << "Assignment operator called" << std::endl;
    this->_value = copy.getRawBits();
    return (*this);
}

int     Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->_value);    
}

void    Fixed::setRawBits(const int raw)
{
    this->_value = raw;
}
