/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 05:49:10 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 06:50:55 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name): _weapon(NULL)
{
    this->_name = name;
    std::cout << "HumanB " << name << " created weaponless." << std::endl;
}

HumanB::~HumanB(void)
{
    std::cout << "HumanB " << this->_name << " destroyed." << std::endl;
}

void HumanB::attack(void)
{
    std::cout << this->_name << " attack with his " << this->_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon)
{
    this->_weapon = &weapon;
}
