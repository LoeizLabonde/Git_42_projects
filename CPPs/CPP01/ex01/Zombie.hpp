/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:12:03 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/08 13:59:43 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

class Zombie {
    
        public :
                Zombie();
                ~Zombie();
                void announce(void)const;
                void set_Name(std::string name);
                
        private :
                std::string  _name;
};

Zombie *zombieHorde(int N, std::string name);
