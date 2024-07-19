/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:14:36 by ticouvre          #+#    #+#             */
/*   Updated: 2024/01/12 10:59:42 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 == 0 && n == 0)
		return (NULL);
	if (ft_strlen(s2) == 0)
		return ((char *) s1);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] && s1[i + j] == s2[j] && i + j < n)
			j++;
		if (s2[j] == '\0')
			return ((char *) s1 + i);
		i++;
	}
	return (NULL);
}
