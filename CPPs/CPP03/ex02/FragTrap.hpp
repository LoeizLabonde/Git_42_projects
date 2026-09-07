/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:04:54 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/05 12:18:16 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap 
{
    public:
            FragTrap(void);
            FragTrap(const FragTrap &copy);
            FragTrap(std::string name);

            ~FragTrap();

            FragTrap &operator=(const FragTrap &src);
            void highFivesGuys(void);
};

#endif