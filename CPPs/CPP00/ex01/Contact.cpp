/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:01:19 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/02 16:03:36 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "repertory.hpp"

Contact::Contact(void){
}

Contact::~Contact(void){
}

void    Contact::setName(str name){
    this->name = name;
}

void    Contact::setLast(str last){
    this->last = last;
}

void    Contact::setNick(str nick){
    this->nick = nick;
}

void    Contact::setPhone(str phone){
    this->phone = phone;
}

void    Contact::setSecret(str secret){
    this->secret = secret;
}

str     Contact::getName() const {
    return this->name;
}

str     Contact::getLast() const {
    return this->last;
}

str     Contact::getNick() const {
    return this->nick;
}

str     Contact::getPhone() const {
    return this->phone;
}

str     Contact::getSecret() const {
    return this->secret;
}
