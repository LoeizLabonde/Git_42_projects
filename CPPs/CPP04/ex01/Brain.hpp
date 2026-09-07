/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:08:05 by llabonde          #+#    #+#             */
/*   Updated: 2025/06/12 19:09:08 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

class Brain
{
    private:
           std::string _ideas[100]; 
    public:
            Brain();
            Brain(const Brain &copy);
            virtual ~Brain();
            Brain &operator=(const Brain &src);       
            
            const std::string getIdea(unsigned int i)const;
            const std::string *getIdeaAddress(unsigned int i)const;

            void setIdea(unsigned int i, std::string idea);
};

#endif