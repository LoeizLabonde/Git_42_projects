/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 05:32:06 by llabonde          #+#    #+#             */
/*   Updated: 2025/09/30 05:32:06 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iter.hpp"

// Exemple de fonction qui modifie l’élément
void increment(int &x)
{
    x++;
}

// Exemple de fonction qui ne fait que lire l’élément
void printInt(const int &x)
{
    std::cout << x << " ";
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    const int carr[] = {10, 20, 30, 40, 50};

    std::cout << "Tableau arr avant increment: ";
    iter(arr, 5, printInt);
    std::cout << std::endl;

    iter(arr, 5, increment); // on modifie

    std::cout << "Tableau arr après increment: ";
    iter(arr, 5, printInt);
    std::cout << std::endl;

    std::cout << "Tableau const carr: ";
    iter(carr, 5, printInt); // fonctionne car printInt prend un const&
    std::cout << std::endl;

    // ⚠️ iter(carr, 5, increment); // interdit : carr est const

    return 0;
}
