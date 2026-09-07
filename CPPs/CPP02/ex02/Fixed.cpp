/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:14:27 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/19 14:33:29 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

static float ft_pow(float base, int exp)
{
    float result;

    if (!exp)
        return 1;
    if (exp < 0)
    {
        base = 1 / base;
        exp *= -1;
    }
    result = base;
    while (--exp)
        result *= base;
    return (result);
}

const int   Fixed::_frac = 8;

Fixed::Fixed(void): _value(0)
{
    std::cout << "Fixed object created with default constructor" << std::endl;
}

Fixed::Fixed(const int value): _value(value * ft_pow(2, this->_frac))
{
    std::cout << "Fixed object created with int constructor" << std::endl;
}

Fixed::Fixed(const float nbr)
{
    int	fractional;
	int	integer;

	std::cout << "Float constructor called" << std::endl;
	integer = nbr;
	fractional = roundf((nbr - integer) * pow(2, 8));
	_value = integer << _frac;
	_value += fractional;

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

float Fixed::toFloat(void) const
{
        return (this->_value * ft_pow(2, -this->_frac));
}

int Fixed::toInt(void) const
{
    return (this->_value * ft_pow(2, -this->_frac));
}

Fixed &Fixed::operator=(Fixed const &copy)
{
    std::cout << "Assignment operator called" << std::endl;
    this->_value = copy.getRawBits();
    return (*this);
}

Fixed Fixed::operator+(Fixed const &copy) const
{
    Fixed result(this->toFloat() + copy.toFloat());
    return (result);
}

Fixed Fixed::operator-(Fixed const &copy) const
{
    Fixed result(this->toFloat() - copy.toFloat());
    return (result);
}

Fixed Fixed::operator*(Fixed const &copy) const
{
    Fixed result(this->toFloat() *copy.toFloat());
    return (result);
}

Fixed Fixed::operator/(Fixed const &copy) const
{
    Fixed result(this->toFloat() / copy.toFloat());
    return (result);
}

bool	Fixed::operator==(const Fixed &copy) const
{
	return (this->toFloat() == copy.toFloat());
}

bool	Fixed::operator!=(const Fixed &copy) const
{
	return (this->toFloat() != copy.toFloat());
}

bool	Fixed::operator<=(const Fixed &copy) const
{
	return (this->toFloat() <= copy.toFloat());
}

bool	Fixed::operator>=(const Fixed &copy) const
{
	return (this->toFloat() >= copy.toFloat());
}

bool	Fixed::operator<(const Fixed &copy) const
{
	return (this->toFloat() < copy.toFloat());
}

bool	Fixed::operator>(const Fixed &copy) const
{
	return (this->toFloat() > copy.toFloat());
}

Fixed	&Fixed::operator++(void)
{
	this->setRawBits(this->getRawBits() + 1);
	return (*this);
}

Fixed	&Fixed::operator--(void)
{
	this->setRawBits(this->getRawBits() - 1);
	return (*this);
}

Fixed Fixed::operator++(int value)
{
    Fixed aux;

    aux = *this;

    if(!value)
        value = 1;
    this->setRawBits(this->getRawBits() + value);
    return (aux);
}

Fixed Fixed::operator--(int value)
{
    Fixed aux;

    aux = *this;

    if (!value)
        value = 1;
    this->setRawBits(this->getRawBits() - value);
    return (aux);
}

const Fixed &Fixed::min(Fixed const &copy1, Fixed const &copy2)
{
    if (copy1 < copy2)
        return (copy1);
    return (copy2);
}

const Fixed &Fixed::max(Fixed const &copy1, Fixed const &copy2)
{
    if (copy1 > copy2)
        return (copy1);
    return (copy2);
}

int Fixed::getRawBits(void) const
{
    return (this->_value);    
}

void    Fixed::setRawBits(const int raw)
{
    this->_value = raw;
}

std::ostream    &operator<<(std::ostream &str, Fixed const &fixed_nbr)
{
    return (str << fixed_nbr.toFloat());
}
