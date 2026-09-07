/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:42 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 18:35:35 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(): Animal()
{
    this->type = "Cat";
    std::cout << "Cat Default Constructor called" << std::endl;
    this->_brain = new Brain();
    if (this->_brain == NULL)
    {
        perror("Cat Brain allocation failed");
        std::cerr << "Exiting process." << std::endl;
        exit(1);
    }
}

Cat::Cat(const Cat &copy)
{
    std::cout << "Cat Copy Constructor called" << std::endl;
    *this = copy;
}

Cat::~Cat()
{
    delete(this->_brain);
    std::cout << "Default Cat Destructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &src)
{
    std::cout << "Cat Assignation operator called" << std::endl;
    if (this == &src)
        return *this;

    this->type = src.type;
    this->_brain = new Brain();
    if (this->_brain == NULL)
    {
        perror("Cat Brain allocation failed");
        std::cerr << "Exiting process." << std::endl;
        exit(1);
    }
    *this->_brain = *src._brain;
    return *this;
}

void Cat::makeSound()const
{    
    std::cout << this->getType() << " says: MEOWMEOWIMACAAAAAAAAAAAAAAAAAAT" << std::endl;
}

void Cat::getIdeas()const
{
    for(int i = 0; i < 3; i++)//i can be modified to see all ideas
        std::cout << "Idea  " << i << "  of the Cat is: -" << this->_brain->getIdea(i) << "- at the address " << this->_brain->getIdeaAddress(i) << std::endl;
}

void Cat::setIdeas(unsigned int i, std::string idea)const
{
    this->_brain->setIdea(i, idea);
}

