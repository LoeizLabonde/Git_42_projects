/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:38 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 17:05:04 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include "Animal.hpp"

class Cat : public Animal
{
    public:
            Cat();
            Cat(const Cat &copy);
            ~Cat();
            Cat &operator=(const Cat &src);
            void makeSound()const;

    private:
            
};

#endif