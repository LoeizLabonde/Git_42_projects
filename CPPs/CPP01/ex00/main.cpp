/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:36:54 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/08 13:09:14 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

//Un->announce(); Doesnt work because Un is not instanciated.
//randomChump can announce itself when its constructor is called. But not after that.
//Trois can announce itself when its constructor is called. AND after that, because 
//he is instanciated. As long as it is not deleted, it exists.

int main(void)
{
    Zombie("Un");
    randomChump("Deux");
    Zombie *trois = newZombie("Trois");
    trois->announce();
    delete trois;
    return (EXIT_SUCCESS);
}
