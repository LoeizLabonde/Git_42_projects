/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:04:51 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/06 11:05:50 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{
    this->_name = "DefFragTrap";
    this->_AttackDamage = 30;
    this->_HitPoints = 100;
    this->_EnergyPoints = 100;
    std::cout << "Default FragTrap Constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
    this->_AttackDamage = 30;
    this->_HitPoints = 100;
    this->_EnergyPoints = 100;
    this->_name = name;
    std::cout << "Named FragTrap Constructor called : " << this->_name << " is ready to ask HighFives!!" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy): ClapTrap(copy)
{
    *this = copy;
    std::cout << "FragTrap Copy-Constructor called" << std::endl;
}

FragTrap::~FragTrap()
{
    std::cout << "Default FragTrap Destructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &src)
{
    std::cout << "FragTrap Assignation operator called" << std::endl;
    this->_name = src._name;
    this->_HitPoints = src._HitPoints;
    this->_EnergyPoints = src._EnergyPoints;
    this->_AttackDamage = src._AttackDamage;
    return *this;
}

void FragTrap::highFivesGuys()
{
    if (this->_EnergyPoints > 0 && this->_HitPoints > 0)
    {
        std::cout << this->_name << " is requesting a HighFives!" << std::endl;
        this->_EnergyPoints--;
    }
    else
        std::cout << this->_name << " is not in capability to do anything, it's EnergyPoints or HitPoints are too low" << std::endl;
}
