/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:16:35 by ticouvre          #+#    #+#             */
/*   Updated: 2024/05/23 16:02:38 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	in_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*dest;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && in_set(s1[start], (char *)set))
		start++;
	while (s1[end] && in_set(s1[end], (char *)set) && end > 0)
		end--;
	if ((end == 0 && start == ft_strlen(s1)))
	{
		dest = malloc(sizeof(char) * 1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	else
		return (ft_strndup((char *)s1 + start, (size_t)end - start + 1));
}
