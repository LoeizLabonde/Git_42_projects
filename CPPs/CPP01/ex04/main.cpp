/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 07:23:52 by llabonde          #+#    #+#             */
/*   Updated: 2025/05/06 11:38:23 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

int replace(char **argv, std::string str)
{
    std::ofstream outfile;
    int           pos;

    outfile.open((std::string(argv[1]) + ".replace").c_str());
    if(outfile.fail())
        return (1);
    for (int i = 0; i < (int)str.size(); i++)
    {
        pos = str.find(argv[2], i);
        if (pos != -1 && pos == i)
        {
            outfile << argv[3];
            i += std::string(argv[2]).size() - 1;
        }
        else
            outfile << str[i];
    }
    outfile.close();
    return (0);
}

int main(int argc, char **argv)
{
    char    c;
    std::ifstream infile;
    std::string   str;

    if (argc != 4)
    {
        std::cout << "usage: replace <file> old_word new_word" << std::endl;
        return (1);
    }
    infile.open(argv[1]);
    if (infile.fail())
    {
        std::cout << "Error: " << argv[1] << ":" << " no such file or directory" << std::endl;
        return (1);
    }
    while (!infile.eof() && infile >> std::noskipws >> c)
        str += c;
    infile.close();
    return (replace(argv, str));
}
