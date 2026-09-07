/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 05:49:13 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 06:43:34 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanB
{
            private :
                    std::string _name;
                    Weapon      *_weapon;
            public :
                    HumanB(std::string name);
                    ~HumanB(void);
                    void attack(void);
                    void setWeapon(Weapon &weapon);
};
