/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:37:39 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/08 12:10:20 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

class Zombie {
    
        public :
                Zombie(std::string s);
                ~Zombie();
                void announce(void)const;
                
        private :
                std::string  _name;
};

Zombie* newZombie( std::string name);
void  randomChump( std::string name);
