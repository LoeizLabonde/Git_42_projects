/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:30:56 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/06 11:07:12 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
    this->_guardingGate = false;
    this->_AttackDamage = 20;
    this->_EnergyPoints = 50;
    this->_HitPoints = 100;
    this->_name = "DefScavTrap";
    std::cout << "Default ScavTrap Constructor called\n";
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
    this->_guardingGate = false;
    this->_AttackDamage = 20;
    this->_EnergyPoints = 50;
    this->_HitPoints = 100;
    this->_name = name;
    std::cout << "Named ScavTrap Constructor called : " << this->_name << " comes to life!\n"; 
}

ScavTrap::ScavTrap(const ScavTrap &copy): ClapTrap(copy)
{
    *this = copy;
    std::cout << "ScavTrap copy Constructor called\n";
}

ScavTrap::~ScavTrap()
{
    std::cout << "Default ScavTrap Destructor called\n";
}

ScavTrap &ScavTrap::operator=(const ScavTrap &src)
{
    std::cout << "ScavTrap Assignation operator called" << std::endl;
    this->_name = src._name;
    this->_HitPoints = src._HitPoints;
    this->_EnergyPoints = src._EnergyPoints;
    this->_AttackDamage = src._AttackDamage;
    return *this;
}

void ScavTrap::attack(const std::string &target)
{
    if (this->_HitPoints > 0 && this->_EnergyPoints > 0)
    {
        std::cout << "ScavTrap named " << this->_name << " launched an attack at " << target << "! It caused " << this->_AttackDamage << " points of damages!" << std::endl;
        this->_EnergyPoints--;
    }
    else if (this->_HitPoints == 0)
        std::cout << "ScavTrap named " << this->_name << " is not in capability to launch an attack because its HitPoints are too low!" << std::endl;
    else
        std::cout << "ScavTrap named " << this->_name << " is not in capability to launch an attack because its Energypoints are too low!" << std::endl;
}

void ScavTrap::guardGate()
{
    if (this->_EnergyPoints > 0 && this->_HitPoints > 0)
    {
        if (this->_guardingGate)
            std::cout << "Already in guarding mode.\n"; 
        else
        {
            this->_guardingGate = true;
            std::cout << "ScavTrap " << this->_name << " is now in guarding mode\n";
            this->_EnergyPoints--; 
        }
    }
    else
        std::cout << this->_name << " is not in capability to do anything, it's EnergyPoints or HitPoints are too low" << std::endl;
}
