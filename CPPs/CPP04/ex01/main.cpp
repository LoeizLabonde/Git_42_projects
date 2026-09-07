/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:46:54 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 20:42:38 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"



int main()
{
    std::cout << "--Phase 1--" << std::endl;
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    
    delete j;//should not create a leak
    delete i;
    std::cout << "--Phase 1 end--" << std::endl;
    std::cout << "--Phase 2--" << std::endl;
    const Animal *Horde[10];
    for (int i = 0; i < 10; i++)
    {
        if (i % 2)
            Horde[i] = new Dog();
        else
            Horde[i] = new Cat();
    }
    for (int i = 0; i < 10; i++)
    {
        std::cout << std::endl;
        std::cout << "Animal type: " << Horde[i]->getType() << std::endl;
        Horde[i]->makeSound();
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for(int i = 0; i< 10;i++)
        delete(Horde[i]);
    std::cout << "--Phase 2 end--" << std::endl;

    std::cout << "--Phase 3--" << std::endl;
    Dog *a = new Dog();
    a->setIdeas(0, "EAT!");
    a->setIdeas(1, "SNIFF!");
    a->setIdeas(2, "SLEEP!");
    a->setIdeas(101, "Invalid idea");
    Dog *b = new Dog(*a);

    std::cout << "A's Ideas : " << std::endl;
    a->getIdeas();
    delete(a);
    std::cout << "B's Ideas : " << std::endl;
    b->getIdeas();
    delete(b);
    std::cout << "--Phase 3 end--" << std::endl;

    return 0;
}