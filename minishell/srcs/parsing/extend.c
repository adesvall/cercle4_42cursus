/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: upeyret <upeyret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:36:49 by adesvall          #+#    #+#             */
/*   Updated: 2021/12/12 18:18:41 by upeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extend_var(char *str, int i, t_list **lst)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = i;
	i++;
	if (str[i] == '?')
	{
		ft_lstadd_back(lst, ft_lstnew(ft_itoa(g.exit_status)));
		return (i + 1);
	}	
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var_name = ft_strndup(&str[start + 1], i - 1 - start);
	var_value = get_var(g.env, var_name);
	free(var_name);
	if (!var_value)
		var_value = "zrgz";
	else
		ft_lstadd_back(lst, ft_lstnew(ft_strdup(var_value)));
	return (i);
}

int	extend_quotes(char *str, int i, t_list **lst, int and_vars)
{
	int		start;

	i++;
	while (str[i] && str[i] != '"')
	{
		start = i;
		while (str[i] && !ft_isin(str[i], "\"") && (!and_vars || str[i] != '$'))
			i++;
		ft_lstadd_back(lst, ft_lstnew(ft_strndup(&str[start], i - start)));
		if (str[i] == '$' && and_vars)
			i = extend_var(str, i, lst);
	}
	return (i);
}

/*
* ft_extend est une fonction qui enleve les guillemets de type ' et "
* et remplace le nom des variables d'environnement par leurs valeurs
*/

char	*ft_extend(char *str, int extend_v, int extend_q)
{
	t_list	*lst;
	int		i;
	int 	start;

	lst = NULL;
	i = 0;
	//printf("%s\n", str);
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		start = i;
		while (str[i] && (!extend_v || str[i] != '$') && (!extend_q || !ft_isin(str[i], "\'\"")))
			i++;
		ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&str[start], i - start)));
		start = i;
		if (str[i] == '\'' && extend_q) // attention si extend q faux les variables a l interrieur vont s extend qd meme
		{
			i = skip_quotes(str, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&str[start + 1], i - 2 - start)));
		}
		else if (str[i] == '\"' && extend_q)
			i = extend_quotes(str, i, &lst, extend_v);
		else if (str[i] == '$' && extend_v)
			i = extend_var(str, i, &lst);
	}
	free(str);
	return (ft_lstjoin(lst));
}
