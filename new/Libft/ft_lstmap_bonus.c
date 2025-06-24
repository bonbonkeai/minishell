/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:27:34 by jdu               #+#    #+#             */
/*   Updated: 2024/11/20 13:27:35 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*p;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		p = f(lst->content);
		new_node = ft_lstnew(p);
		if (!new_node)
		{
			del(p);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*p;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (NULL);
	new_node = new_lst;
	lst = lst->next;
	while (lst)
	{
		p = f(lst->content);
		new_node->next = ft_lstnew(p);
		if (!new_node->next)
		{
			del(p);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		//ft_lstadd_back(&new_lst, new_node);
		new_node = new_node->next;
		lst = lst->next;
	}
	return (new_lst);
}*/
