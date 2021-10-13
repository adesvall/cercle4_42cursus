/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:40:18 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/13 12:36:50 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	word;
	int	count;

	i = 0;
	word = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (word == 0 && s[i] != c)
		{
			word = 1;
			count++;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

char	*ft_strdup_chr(const char *str, char c)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (res == 0)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_abort(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		i;
	int		count;
	int		word;

	res = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!s || !res)
		return (0);
	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (word == 0 && s[i] != c)
		{
			res[count] = ft_strdup_chr(&(s[i]), c);
			if (res[count++] == 0)
				return (ft_abort(res));
			word = 1;
		}
		if (s[i++] == c)
			word = 0;
	}
	res[count] = NULL;
	return (res);
}
