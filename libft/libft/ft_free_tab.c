/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:20:42 by ticouvre          #+#    #+#             */
/*   Updated: 2024/05/31 12:22:55 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	if (n)
	{
		while (i < n)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	else
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
