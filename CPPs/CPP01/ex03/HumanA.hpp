/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 05:49:07 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 06:29:59 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanA
{
            private :
                    std::string _name;
                    Weapon      &_weapon;
            public :
                    HumanA(std::string name, Weapon &weapon);
                    ~HumanA(void);
                    void attack(void);
                    void setWeapon(Weapon weapon);
};

