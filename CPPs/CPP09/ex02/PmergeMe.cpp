/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 06:58:37 by llabonde          #+#    #+#             */
/*   Updated: 2025/10/16 07:45:50 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : m_data(other.m_data), m_deq(other.m_deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        m_data = other.m_data;
        m_deq = other.m_deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::setData(const std::vector<int>& data)
{
    m_data = data;
}

void PmergeMe::setDeq(const std::deque<int>& deq)
{
    m_deq = deq;
}

std::vector<int>& PmergeMe::getData()
{
    return m_data;
}

std::deque<int>& PmergeMe::getDeq()
{
    return m_deq;
}
