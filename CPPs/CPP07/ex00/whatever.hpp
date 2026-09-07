/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 08:59:43 by llabonde          #+#    #+#             */
/*   Updated: 2025/10/02 08:59:43 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template< typename T >// defines T as a template
const T &max(const T &x ,const T &y)
{
    return (x >= y ? x : y);
}

template< typename R >
const R &min(const R &x ,const R &y)
{
    return (x <= y ? x : y);
}

template< typename V >
void swap(V &x, V &y)
{
    V temp = x;
    x = y;
    y = temp;
}
