/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 04:30:45 by llabonde          #+#    #+#             */
/*   Updated: 2025/09/29 04:30:45 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(): _size(0), _pos(0)
{

}

Span::Span(unsigned int N): _size(N), _pos(0)
{
    std::cout << "Span Constructor for size of " << N << " called" << std::endl;
    this->_storage.reserve(this->getSize());
}

Span::Span(const Span &src): _size(src.getSize()), _pos(src.getPos())
{
    std::cout << "Span Copy Constructor called" << std::endl;
    *this = src;
}

Span::~Span()
{
    std::cout << "Span Deconstructor called" << std::endl;
}

Span &Span::operator=(const Span &src)
{
    std::cout << "span Assignation operator called" << std::endl;
    if (this == &src)
        return *this;
    return *this;
}

void    Span::addNumber(int number)
{
    if ((this->_pos != 0 && this->_storage.empty() == true) || this->_storage.max_size() < this->getSize())
        throw (Span::VectorInvalidException());
    if (this->getPos() + 1 > this->getSize())
        throw (Span::ArrayFullException());
    else
    {
        this->_pos++;
        this->_storage.push_back(number);
    }
}

void    Span::addNumber(unsigned int range, time_t seed)
{
    srand(seed);
    for(size_t i = 0; i < range; i++)
    {
        try
        {
           addNumber(rand());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

unsigned int Span::shortestSpan(void) const
{
    if (this->_pos == 1 || this->_storage.size() == 1)
        throw (Span::ComparisonInvalidException());
    
    std::vector<int> v (this->_storage);
    std::sort (v.begin(), v.end());

    unsigned int ret = UINT_MAX;
    std::vector<int>::iterator temp_it = v.begin();
    std::vector<int>::iterator temp_it_next = v.begin() + 1;
    while (temp_it_next != v.end())
    {
        if ((unsigned int)(*temp_it_next - *temp_it) < ret)
            ret = *temp_it_next - *temp_it;
        ++temp_it_next;
        ++temp_it;
    }
    return (ret);
}

unsigned int Span::longestSpan(void) const
{
    if (this->_pos == 1 || this->_storage.size() == 1)
        throw(Span::ComparisonInvalidException());

    std::vector<int> v(this->_storage);
    int low, high;

    std::sort (v.rbegin(), v.rend());
    high = *v.begin();

    std::sort (v.begin(), v.end());
    low = *v.begin();

    return (high - low);
}

unsigned int Span::getSize() const
{
    return (this->_size);
}

unsigned int  Span::getPos() const
{
    return (this->_pos);
}

const char	*Span::VectorInvalidException::what() const throw()
{
	return ("Error: Invalid or broken vector");
}

const char	*Span::ArrayFullException::what() const throw()
{
	return ("Error: Array full");
}

const char	*Span::ComparisonInvalidException::what() const throw()
{
	return ("Error: more than one element in vector needed to be compared");
}
