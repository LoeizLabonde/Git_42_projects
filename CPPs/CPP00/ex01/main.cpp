/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:07:06 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/02 16:03:40 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "repertory.hpp"

int     main() {
        PhoneBook      PhoneBook;

        str             line;
        str             add = "ADD";
        str             search = "SEARCH";
        str             exit = "EXIT";

        system("clear");
        std::cout << "Hello ! Welcome to your crappy awesome contact manager." << std::endl;
        while(1)
        {
            std::cout << "Please enter ADD, SEARCH or EXIT : ";
            std::getline(std::cin, line);
            if (!line.compare(add))
                PhoneBook.add_contact();
            else if (!line.compare(search))
                PhoneBook.search_contact();
            else if (!line.compare(exit))
            {
                std::cout << "Goodbye !" << std::endl;
                break;
            }
            system("clear");
        }
        sleep(2);
        return (0);
}
