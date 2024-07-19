/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:12:28 by ticouvre          #+#    #+#             */
/*   Updated: 2024/01/12 10:58:29 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*debut;
	t_list	*actuel;

	if (!lst ||!del)
		return (NULL);
	debut = ft_lstnew(f(lst->content));
	actuel = debut;
	while (lst && lst->next)
	{
		if (!actuel)
			return (NULL);
		actuel->next = ft_lstnew(f(lst->next->content));
		actuel = actuel->next;
		lst = lst->next;
	}
	return (debut);
}
