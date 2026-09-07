/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:49:02 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/24 15:45:32 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*tmp;
	void	*set;

	if (!lst || !f || !del)
		return (0);
	nlst = NULL;
	while (lst)
	{
		set = f(lst->content);
		tmp = ft_lstnew(set);
		if (!tmp)
		{
			del(set);
			ft_lstclear(&nlst, (*del));
			return (nlst);
		}
		ft_lstadd_back(&nlst, tmp);
		lst = lst->next;
	}
	return (nlst);
}
