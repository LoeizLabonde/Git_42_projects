/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 05:49:04 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 06:56:57 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon): _name(name), _weapon(weapon)
{
    std::cout << "HumanA " << name << " created with " << weapon.getType() << std::endl;
}

HumanA::~HumanA(void)
{
    std::cout << "HumanA " << this->_name << " destroyed." << std::endl;
}

void HumanA::attack(void)
{
    std::cout << this->_name << " attacks whith his " << this->_weapon.getType() << std::endl;
}

void HumanA::setWeapon(Weapon weapon)
{
    this->_weapon = weapon;
}
