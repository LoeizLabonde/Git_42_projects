/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:57:14 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/06 11:17:50 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap un;
    ClapTrap deux("Two");
    ClapTrap trois("Trois");
    
    trois = deux;
    un.attack("the wall");
    un.takeDamage(7);
    un.beRepaired(5);
    un.beRepaired(11);
    un.takeDamage(700);
    un.takeDamage(99999);
    un.beRepaired(5);
    deux.beRepaired(5);
    for (int i = 0; i < 12; i++)
        deux.attack("the floor");
    deux.beRepaired(1);
    return 0;
}
