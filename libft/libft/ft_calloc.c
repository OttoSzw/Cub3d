/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:23:39 by ticouvre          #+#    #+#             */
/*   Updated: 2024/01/12 10:56:53 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nb, size_t size)
{
	void	*dest;

	if (nb == 0 || size == 0)
	{
		nb = 1;
		size = 1;
	}
	if (nb > SIZE_MAX / size)
		return (NULL);
	dest = malloc(nb * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nb * size);
	return (dest);
}
