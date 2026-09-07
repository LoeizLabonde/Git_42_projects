/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:04:48 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/05 12:05:37 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP

# define CLAPTRAP_HPP

# include <string>
# include <iostream>

class ClapTrap
{
    protected:
    
        std::string _name;
        unsigned int _HitPoints;
        unsigned int _EnergyPoints;
        unsigned int _AttackDamage;
        
    public:
        ClapTrap(void);
        ClapTrap(const ClapTrap  &copy);
        ClapTrap(std::string name);
    
        ~ClapTrap();
        
        ClapTrap &operator=(const ClapTrap &src);
        void attack(const std::string &target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        
};

#endif