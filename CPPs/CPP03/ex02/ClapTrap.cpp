/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:04:45 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/05 12:05:25 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): _name("ClapTrap"), _HitPoints(10), _EnergyPoints(10), _AttackDamage(0)
{
    std::cout << "ClapTrap default constructor called"  << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy)
{
    std::cout << "ClapTrap copy Constructor called" << std::endl;
    *this = copy;
}

ClapTrap::ClapTrap(std::string name): _name(name), _HitPoints(10), _EnergyPoints(10), _AttackDamage(0)
{
    std::cout << "ClapTrap named-Constructor called: " << _name << " comes to life!" << std::endl; 
}

ClapTrap::~ClapTrap()
{
    std::cout << "Default Destructor called: " << _name << " is destroyed" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src)
{
    std::cout << "ClapTrap Assignation operator called" << std::endl;
    this->_name = src._name;
    this->_HitPoints = src._HitPoints;
    this->_EnergyPoints = src._EnergyPoints;
    this->_AttackDamage = src._AttackDamage;
    return *this;
}

void ClapTrap::attack(const std::string &target)
{
    if (this->_HitPoints > 0 && this->_EnergyPoints > 0)
    {
        std::cout << "ClapTrap named " << this->_name << " launched an attack at " << target << "! It caused " << this->_AttackDamage << " points of damages!" << std::endl;
        this->_EnergyPoints--;
    }
    else if (this->_HitPoints == 0)
        std::cout << "ClapTrap named " << this->_name << " is not in capability to launch an attack because its HitPoints are too low!" << std::endl;
    else
        std::cout << "ClapTrap named " << this->_name << " is not in capability to launch an attack because its Energypoints are too low!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->_HitPoints > amount)
    {
        this->_HitPoints -= amount;
        std::cout << "ClapTrap " << this->_name << " takes " << amount << " points of damage! It's Hitpoints are now : " << this->_HitPoints << std::endl;
    }
    else if (this->_HitPoints > 0)
    {
        this->_HitPoints = 0;
        std::cout << "ClapTrap " << this->_name << " takes way too much points of damage! It's Hitpoints are now : 0!" << std::endl;
    }
    else
        std::cout << "This ClapTrap " << this->_name <<  " can't take it anymore. Even if it deserves it, please stop hitting it." << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_HitPoints > 0 && this->_EnergyPoints > 0 && amount <= 10)
    {
        if (amount + this->_HitPoints > 100)
        {
            std::cout << "ClapTrap named " << this->_name << " can't repair itself over its max capability." << std::endl;
            return ;
        }
        else
        {
            this->_HitPoints += amount;
            std::cout << "ClapTrap named " << this->_name << " repairs itself and gains " << amount << " Hitpoints. It now has " << this->_HitPoints << " Hitpoints."  << std::endl;
            return ;
        }
    }
    else if (amount > 10)
        std::cout << "ClapTrap named " << this->_name << " can't repair itself for an amount over 10, nice try tho\n";
    else if (this->_EnergyPoints == 0)
        std::cout << "ClapTrap named " << this->_name << " is not in capability to repair itself because it's Energypoints are too low!" << std::endl;
    else if (this->_HitPoints == 0)
        std::cout << "ClapTrap named " << this->_name << " is not in capability to repair itself because it's HitPoints are too low!" << std::endl;    
}
