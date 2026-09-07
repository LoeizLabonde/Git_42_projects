/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:11:36 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 05:14:33 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie *horde;
    int    nbZombie = 10;

    horde = zombieHorde(nbZombie, "Horde Fellow");
    if (horde == NULL)
        return (EXIT_FAILURE);
    for(int i = 0; i < nbZombie; i++)
        horde[i].announce();
    delete[] horde;
    return (EXIT_SUCCESS);
}
