/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:07:17 by llabonde          #+#    #+#             */
/*   Updated: 2025/04/02 16:03:31 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
#define CONTACT_H

#include "repertory.hpp"

class   Contact {
        public :
                Contact(void);
                ~Contact(void);

                void    setName(str name);
                void    setLast(str last);
                void    setNick(str nick);
                void    setPhone(str phone);
                void    setSecret(str secret);
                str     getName() const;
                str     getLast() const;
                str     getNick() const;
                str     getPhone() const;
                str     getSecret() const;
        
        private :
                str     name;
                str     last;
                str     nick;
                str     phone;
                str     secret;

};

#endif
