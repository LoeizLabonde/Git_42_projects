/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:12:17 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/08 14:05:05 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
    if (N < 1)
    {
        std::cout << "Invalid parameter, N must be at least superior to 0." << std::endl;
    }
    Zombie *horde = new Zombie[N];
    if (horde == NULL)
    {
        std::cout << "Something went wrong on allocation." << std::endl;
        return (NULL);
    }
    for (int i = 0; i < N; i++)
        horde[i].set_Name(name);
    return (horde);
}
