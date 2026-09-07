/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 06:57:06 by llabonde          #+#    #+#             */
/*   Updated: 2025/10/16 07:46:02 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once


#include <vector>
#include <deque>
#include <iostream>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <climits>
#include "PmergeMe.tpp"


#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1

#define GREY        "\033[0;30m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"

/* Definitions of ANSI bright color codes for console output */ 
#define BRIGHT_GREY    "\033[1;30m"
#define BRIGHT_RED     "\033[1;31m"
#define BRIGHT_GREEN   "\033[1;32m"
#define BRIGHT_YELLOW  "\033[1;33m"
#define BRIGHT_BLUE    "\033[1;34m"
#define BRIGHT_MAGENTA "\033[1;35m"
#define BRIGHT_CYAN    "\033[1;36m"
#define BRIGHT_WHITE   "\033[1;37m"

/* Definitions of ANSI background color codes for console output */
#define BLACK_BG       "\033[40m"
#define RED_BG         "\033[41m"
#define GREEN_BG       "\033[42m"
#define YELLOW_BG      "\033[43m"
#define BLUE_BG        "\033[44m"
#define MAGENTA_BG     "\033[45m"
#define CYAN_BG        "\033[46m"
#define WHITE_BG       "\033[47m"

/* Definitions of ANSI text style codes for console output */
#define BOLD           "\033[1m"
#define UNDERLINE      "\033[4m"
#define RESET          "\033[0m"

/* No Color */
#define NC             RESET
/* 1000 a 4 chiffres */
#define MAX_DIGITS 4

/* Define return values */
#define ARG_ONE 2
#define ARG_TWO 3
#define NO_ARGUMENTS 1
#define RETURN_SUCCESS 0
#define FIRST_ARGUMENT 1
#define SECOND_ARGUMENT 2
#define RETURN_FAILURE 1
#define TEST_ARG "tester"
#define STRING_COMPARE_SUCCESS 0



class PmergeMe
{
    public:
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
        PmergeMe();

        void setData(const std::vector<int>& data);
        void setDeq(const std::deque<int>& deq);
        std::vector<int>& getData();
        std::deque<int>& getDeq();

    private:
        std::vector<int> m_data;
        std::deque<int> m_deq;
};




