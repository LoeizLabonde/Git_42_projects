/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:37:42 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/08 12:46:40 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

//Contructor
Zombie::Zombie(std::string s) : _name(s)
{
    std::cout << "Hello there, I am " << _name << " and I'm coming for you!" << "\n" << std::endl;
}

//Destructor
Zombie::~Zombie()
{
    std::cout << _name << "'s head fell down to the ground and died on the spot!\n" << std::endl;
}

//announce
void  Zombie::announce(void) const
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ...\n" << std::endl;
}
