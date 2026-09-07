/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:10:40 by llabonde          #+#    #+#             */
/*   Updated: 2025/08/29 14:26:09 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main(void)
{
    Data *data = new Data;
    data->name = "Thorfinn";
    data->age = 26;
    data->work = "True Warrior";
    
    uintptr_t raw = Serializer::serialize(data);
    Data *serialized = Serializer::deserialize(raw);

    std::cout << serialized->name << std::endl;
    std::cout << serialized->age << std::endl;
    std::cout << serialized->work << std::endl;
    
    delete data;
    return 0;
}
