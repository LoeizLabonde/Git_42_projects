/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:08:08 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 20:40:58 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain Default Constructor called" << std::endl;
}

Brain::Brain(const Brain &copy)
{
    std::cout << "Brain Copy Constructor called" << std::endl;
    *this = copy;
}

Brain::~Brain()
{
    std::cout << "Default Brain Destructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &src)
{
    std::cout << "Brain Assignation operator called" << std::endl;
    if (this == &src)
        return *this;
    for (int i = 0; i < 100; i++)
    {
        if (src._ideas[i].length() > 0)
            this->_ideas[i].assign(src._ideas[i]);
    }
    return *this;
}

const std::string Brain::getIdea(unsigned int i)const
{
    if (0 <= i < 100)
        return (this->_ideas[i]);
    else
        return ("Input error, index invalid. Try with a number between 0 and 100");
}

const std::string *Brain::getIdeaAddress(unsigned int i)const
{
    if (0 <= i < 100)
    {
        const std::string &stringREF = this->_ideas[i];
        return (&stringREF);
    }
    else
        return (NULL);
}

void Brain::setIdea(unsigned int i, std::string idea)
{
    if (i < 100)
        this->_ideas[i] = idea;
    else
        std::cout << "Input error, index invalid. Try with a number between 0 and 100" << std::endl;
}
