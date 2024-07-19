/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:20:39 by ticouvre          #+#    #+#             */
/*   Updated: 2024/01/12 10:58:05 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_size_malloc(int n)
{
	size_t	size;
	long	nb;

	nb = n;
	size = 0;
	if (nb == 0)
		size = 1;
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb > 0)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	size;
	long	nb;
	char	*dest;

	nb = n;
	size = ft_size_malloc((long) n);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = '\0';
	size--;
	if (nb < 0)
		nb = -nb;
	while (size >= 0)
	{
		dest[size] = nb % 10 + 48;
		size--;
		nb /= 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
