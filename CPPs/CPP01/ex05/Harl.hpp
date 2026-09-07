/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 07:56:22 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 08:04:30 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdlib>

class Harl
{
    private :
            void debug(void);
            void info(void);
            void warning(void);
            void error(void);
    
    public :
            Harl();
            ~Harl();
            void complain(std::string level);
};
