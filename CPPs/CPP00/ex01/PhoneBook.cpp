/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:07:14 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/02 16:03:50 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "repertory.hpp"

PhoneBook::PhoneBook() : current_nb(0), nb_contacts(0) {
}

PhoneBook::~PhoneBook(){
}

void    PhoneBook::add_contact(){
        str     name;
        str     last;
        str     nick;
        str     phone;
        str     secret;

        system("clear");
        if(this->current_nb == 8)
            this->current_nb = 0;
        system("clear");
        while (1)
        {
            std::cout << "Please enter a name :";
            std::getline(std::cin, name);
            if (name.length() != 0)
                break;
            else {
                std::cout << "Field can't be empty, please fill the following line : " << std::endl;
                sleep(2);
                system("clear");
            }
        }
        system("clear");
        while (1)
        {
            std::cout << "Please enter a surname :";
            std::getline(std::cin, last);
            if (last.length() != 0)
                break;
            else {
                std::cout << "Field can't be empty, please fill the following line : " << std::endl;
                sleep(2);
                system("clear");
            }
        }
        system("clear");
        while (1){
            std::cout << "Please enter a nickame :";
            std::getline(std::cin, nick);
            if (nick.length() != 0)
                break;
            else {
                std::cout << "Field can't be empty, please fill the following line : " << std::endl;
                sleep(2);
                system("clear");
            }           
        }
        system("clear");
        while (1){
            std::cout << "Please enter a phone-number :";
            std::getline(std::cin, phone);
            if (phone.length() != 0)
                break;
            else {
                std::cout << "Field can't be empty, please fill the following line : " << std::endl;
                sleep(2);
                system("clear");
            }
        }
        system("clear");
        while (1){
            std::cout << "Please enter a secret :";
            std::getline(std::cin, secret);
            if (secret.length() != 0)
                break;
            else {
                std::cout << "Field can't be empty, please fill the following line : " << std::endl;
                sleep(2);
                system("clear");
            }           
        }
        system("clear");
        this->array[this->current_nb].setName(name);
        this->array[this->current_nb].setLast(last);
        this->array[this->current_nb].setNick(nick);
        this->array[this->current_nb].setPhone(phone);
        this->array[this->current_nb].setSecret(secret);
        this->current_nb++;
        if (nb_contacts < 8)
            nb_contacts++;
        
}

void    PhoneBook::search_contact() {
        int     i = 0;
        str     name;
        str     last;
        str     nick;
        str     phone;
        str     secret;
        str     ret;
        int     index;

        system("clear");
        if(this->current_nb == 0) {
            std::cout << "No contacts yet ! Exiting..." << std::endl; sleep(2); return ;
        }
        std::cout << std::setw(5) << "Index" << "|";
        std::cout << std::setw(10) << "Firstname" << "|";
        std::cout << std::setw(10) << "Lastname" << "|";
        std::cout << std::setw(10) << "Nickname" << std::endl;
        while(i < nb_contacts){
            std::cout << std::setw(5) << i << "|";
            name = this->array[i].getName();
            last = this->array[i].getLast();
            nick = this->array[i].getNick();
            phone = this->array[i].getPhone();
            secret = this->array[i].getSecret();
            if (name.length() > 9)
                name = name.substr(0, 9) + ".";
            if (last.length() > 9)
                last = last.substr(0, 9) + ".";
            if (nick.length() > 9)
                nick = nick.substr(0, 9) + ".";
            std::cout << std::setw(10) << name << "|";
            std::cout << std::setw(10) << last << "|";
            std::cout << std::setw(10) << nick << std::endl;
            i++;
        }
        std::cout << std::endl << "Please enter a contact's Index to display its details : ";
        std::getline(std::cin, ret);
        index = atoi(ret.c_str());
        if ((index == 0 && ret[0] != '0') || (index > 7 || index < 0)) {
            std::cout << "Invalid index! Exiting..." << std::endl; sleep(2); return;
        }
        if (index >= this->nb_contacts) {
            std::cout << "No contact found ! Exiting..." << std::endl; sleep(2); return;
        }
        std::cout << "Name : " << this->array[index].getName() << std::endl;
        std::cout << "Lastname : " << this->array[index].getLast() << std::endl;
        std::cout << "Nickname : " << this->array[index].getNick() << std::endl;
        std::cout << "Phone number : " << this->array[index].getPhone() << std::endl;
        std::cout << "Darkest secret : " << this->array[index].getSecret() << std::endl;
        std::cout << std::endl << "Press a key to continue " << std::endl;
        getchar();
}
