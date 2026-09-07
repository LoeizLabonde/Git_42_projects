/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:10:44 by llabonde          #+#    #+#             */
/*   Updated: 2025/08/29 14:22:56 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer(void)
{

}

Serializer::Serializer(Serializer const &other)
{
    *this = other;
}

Serializer &Serializer::operator=(Serializer const &other)
{
    if (this != &other)
    {
        *this = other;
    }
    return (*this);
}

Serializer::~Serializer(void)
{
    
}

uintptr_t Serializer::serialize(Data* ptr)
{
    return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serializer::deserialize(uintptr_t raw)
{
    return (reinterpret_cast<Data*>(raw));
}
