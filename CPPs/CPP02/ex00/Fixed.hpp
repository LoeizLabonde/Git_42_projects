/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:23 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/19 11:11:27 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP

# define FIXED_HPP

# include <iostream>

class   Fixed
{
        private:
            int                 _value;
            static const int    _frac;
        public:
            Fixed(void);
            ~Fixed(void);
            Fixed(Fixed const &copy);
            Fixed &operator=(Fixed const &copy);
            int getRawBits(void) const;
            void setRawBits(int const raw);
        
};

#endif
