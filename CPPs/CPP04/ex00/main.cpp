/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:51:17 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 14:57:30 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

/*
int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();
    delete meta;
    delete j;
    delete i;
    return 0;
}
int main()
{
    const WrongAnimal* blop = new WrongCat();
    const WrongAnimal* bloptwo = new WrongAnimal();
    const WrongAnimal* blopthree = new WrongCat();

    std::cout << blop->getType() << " " << std::endl;
    std::cout << bloptwo->getType() << " " << std::endl;
    std::cout << blopthree->getType() << " " << std::endl;


    blop->makeSound();
    bloptwo->makeSound();
    blopthree->makeSound();

    delete blop;
    delete bloptwo;
    delete blopthree;
    return 0;
}
*/
int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    const WrongAnimal* blop = new WrongCat();
    const WrongCat* bloptwo = new WrongCat();
    const WrongAnimal* blopthree = new WrongAnimal();

    
    std::cout << meta->getType() << " " <<std::endl;
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    std::cout << blop->getType() << " " << std::endl;
    std::cout << bloptwo->getType() << " " << std::endl;
    std::cout << blopthree->getType() << " " << std::endl;

    
    i->makeSound(); //will output the cat sound!
    j->makeSound();
    meta->makeSound();
    
    blop->makeSound();
    bloptwo->makeSound();
    blopthree->makeSound();

    
    delete meta;
    delete j;
    delete i;
    delete blop;
    delete bloptwo;
    delete blopthree;
    return 0;
}


