/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticouvre <ticouvre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:59:13 by ticouvre          #+#    #+#             */
/*   Updated: 2024/05/23 16:02:21 by ticouvre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	tab_size(char const *s, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			size++;
		i++;
	}
	return (size);
}

static int	ft_strndup_size(char *str, char c)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != c)
		size++;
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		len;
	int		size;

	i = 0;
	j = 0;
	len = (tab_size(s, c));
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		while (s[j] && s[j] == c)
			s++;
		size = ft_strndup_size((char *)s, c);
		tab[i] = ft_strndup((char *)s, (size_t)size);
		s += size;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
