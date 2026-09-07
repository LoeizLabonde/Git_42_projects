/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:07:11 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/02 16:03:44 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "repertory.hpp"

class   PhoneBook {
        public :
            PhoneBook();
            ~PhoneBook();

            void    add_contact();
            void    search_contact();
        
        private :
            int         current_nb;
            int         nb_contacts;
            Contact     array[8];
};

#endif
