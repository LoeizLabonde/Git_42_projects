/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 06:43:45 by llabonde          #+#    #+#             */
/*   Updated: 2025/10/16 07:45:19 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1

class RPN
{
    public:
        RPN();
        RPN(const RPN & other);
        RPN & operator = (const RPN & other);
        ~RPN();
        double evaluate(const std::string & expression);

    private:
        std::stack<double> _stack;
        bool isOperator(const std::string & token);
        double performOperation(const std::string & operation, double operand1, double operand2);
        void validateExpression(const std::string & expression);

};
