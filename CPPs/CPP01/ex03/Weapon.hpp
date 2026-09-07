/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 05:49:20 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 06:52:30 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP

# define WEAPON_HPP

# include <iostream>

class Weapon {
    
        public :
                Weapon(std::string type);
                ~Weapon(void);
                const std::string& getType();
                void setType(std::string newname);
        private :
                std::string _type;
};

#endif
