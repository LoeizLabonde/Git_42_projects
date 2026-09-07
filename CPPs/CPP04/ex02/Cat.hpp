/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:35:38 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 18:19:53 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
    public:
            Cat();
            Cat(const Cat &copy);
            ~Cat();
            Cat &operator=(const Cat &src);
            void makeSound()const;
            void setIdeas(unsigned int i,std::string idea)const;
            void getIdeas()const;

    private:
            Brain* _brain;
};

#endif