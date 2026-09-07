/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:41:59 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/19 12:52:34 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP

# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
    private:
        int _value;
        static const int    _frac;
        
    public:
        Fixed(void);
        Fixed(const int vaue);
        Fixed(const float value);
        ~Fixed(void);
        Fixed(Fixed const &copy);
        Fixed &operator=(Fixed const &copy);
        int getRawBits(void) const;
        void  setRawBits(int const raw);
        float toFloat(void) const;
        int toInt(void) const;
};

std::ostream &operator<<(std::ostream &str, Fixed const &fixed_nbr);

#endif
