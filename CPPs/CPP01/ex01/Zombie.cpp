/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:11:51 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 05:16:14 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

//Contructor
Zombie::Zombie()
{
}

//Destructor
Zombie::~Zombie()
{
    std::cout << _name << "'s head fell down to the ground and died on the spot!" << std::endl;
}

//announce
void  Zombie::announce(void) const
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::set_Name(std::string name)
{
    this->_name = name;
}
