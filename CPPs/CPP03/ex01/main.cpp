/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:10:12 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/06 11:19:05 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

/*
int main()
{
	std::cout << "\n\n### TESTING SCAVTRAP ###\n" << std::endl;
	{
		std::cout << "\033[34mConstructing\033[0m" << std::endl;
		ScavTrap c;
		ScavTrap d("Savage");

		std::cout << "\033[34mTesting\033[0m" << std::endl;
		c.attack("CloneTrap");
		// for (int i = 0; i < 50; i++)
		// 	c.attack("CloneTrap");
		c.beRepaired(22);
		c.takeDamage(21);
		c.beRepaired(8);
		c.guardGate();
		c.guardGate();
		d.attack("Savage-clone");
		d.takeDamage(101);
		d.takeDamage(15);
		d.attack("ScavTrap-clone");
		std::cout << "\033[34mDeconstructing\033[0m" << std::endl;
	}
}
*/

int main()
{
    ScavTrap un;
    ScavTrap deux("Two");
	ScavTrap trois("Trois");
    
	trois = deux;
    un.guardGate();
    un.guardGate();
    deux.guardGate();
    un.attack("the wall");
    un.takeDamage(7);
    un.beRepaired(5);
    un.beRepaired(11);
    un.beRepaired(5);
    un.takeDamage(700);
    un.takeDamage(99999);
    un.beRepaired(5);
    deux.beRepaired(5);
    for (int i = 0; i < 52; i++)
        deux.attack("the floor");
    deux.beRepaired(1);
    return 0;
}
