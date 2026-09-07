/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:47 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 18:42:17 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(): Animal()
{
    this->type = "Dog";
    std::cout << "Dog Default Constructor called" << std::endl;
    this->_brain = new Brain();
    if (this->_brain == NULL)
    {
        perror("Dog Brain allocation failed");
        std::cerr << "Exiting process." << std::endl;
        exit(1);
    }
}

Dog::Dog(const Dog &copy)
{
    std::cout << "Dog Copy Constructor called" << std::endl;
    *this = copy;
}

Dog::~Dog()
{
    delete(this->_brain);
    std::cout << "Default Dog Destructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &src)
{
    std::cout << "Dog Assignation operator called" << std::endl;
    if (this == &src)
        return *this;
    
    this->type = src.type;
    this->_brain = new Brain();
    if (this->_brain == NULL)
    {
        perror("Dog Brain allocation failed");
        std::cerr << "Exiting process." << std::endl;
        exit(1);
    }
    *this->_brain = *src._brain;
    return *this;
}

void Dog::makeSound()const
{
    std::cout << this->getType() << " says: BarkBarkBarkBarkWOUAFWOUAFWOUAFWOUAFIMADOOOOOOOOOOOOG" << std::endl;
}

void Dog::getIdeas()const
{
    for(int i = 0; i < 3; i++)//i can be modified to see all ideas
        std::cout << "Idea  " << i << "  of the Dog is: -" << this->_brain->getIdea(i) << "- at the address " << this->_brain->getIdeaAddress(i) << std::endl;
}

void Dog::setIdeas(unsigned int i, std::string idea)const
{
    this->_brain->setIdea(i, idea);
}
