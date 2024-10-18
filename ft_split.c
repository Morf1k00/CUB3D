/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrechun <rkrechun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:58:06 by rkrechun          #+#    #+#             */
/*   Updated: 2024/10/16 16:58:15 by rkrechun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static char	*ft_dele(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!temp)
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c || (i > 0 && s[i - 1] != c))
			temp[j++] = s[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

static char	**ft_mal_and_wr(char **fin, char *temp, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	g;

	i = 0;
	j = 0;
	while (temp[i] != '\0')
	{
		k = 0;
		g = i;
		while (temp[i] != '\0' && temp[i] != c)
			i++;
		fin[j] = malloc(sizeof(char) * (i - g + 1));
		if (!fin[j])
			return (NULL);
		while (temp[g] != '\0' && temp[g] != c)
			fin[j][k++] = temp[g++];
		fin[j][k] = '\0';
		j++;
		if (temp[i] == c && temp[i] != '\0')
			i++;
	}
	fin[j] = NULL;
	return (fin);
}

char	**ft_split(char const *s, char c)
{
	char	*temp;
	char	**fin;

	if (!s)
		return (NULL);
	temp = ft_dele(s, c);
	if (!temp)
	{
		free (temp);
		return (NULL);
	}
	fin = malloc(sizeof(char *) * (ft_strlen(temp) + 1));
	if (!fin)
	{
		free (temp);
		return (NULL);
	}
	fin = ft_mal_and_wr(fin, temp, c);
	if (!fin)
	{
		free (temp);
		return (NULL);
	}
	free (temp);
	return (fin);
}