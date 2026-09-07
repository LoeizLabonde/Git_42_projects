/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:31:00 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/05 10:56:10 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {

    private:
            bool _guardingGate;
    public :
            ScavTrap(void);
            ScavTrap(const ScavTrap &copy);
            ScavTrap(std::string name);

            ~ScavTrap();

            ScavTrap &operator=(const ScavTrap &src);
            void guardGate();
            void attack(const std::string &target);
            
};

#endif