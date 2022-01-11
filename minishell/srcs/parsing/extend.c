/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:36:49 by adesvall          #+#    #+#             */
/*   Updated: 2022/01/08 14:40:12 by adesvall         ###   ########.fr       */
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
		ft_lstadd_back(lst, ft_lstnew(ft_itoa(g_data.exit_status)));
		return (i + 1);
	}	
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var_name = ft_strndup(&str[start + 1], i - 1 - start);
	var_value = get_var(g_data.env, var_name);
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

int	join_normal(char *str, t_list **lst, int extend_v, int here_doc)
{
	int		i;

	i = 0;
	while (str[i] && (!extend_v || str[i] != '$') \
				&& (here_doc || !ft_isin(str[i], "\'\"")))
		i++;
	ft_lstadd_back(lst, ft_lstnew(ft_strndup(str, i)));
	return (i);
}

int	expand_and_join(char *str, t_list **lst, int extend_v, int extend_q)
{
	int		i;

	i = 0;
	if ((str[i] == '\'' || str[i] == '\"'))
	{
		if (str[i] == '\'' || !extend_q)
		{
			i = skip_quotes(str, i);
			ft_lstadd_back(lst, \
					ft_lstnew(ft_strndup(&str[extend_q], \
									i - 2 * extend_q)));
		}
		else if (str[i] == '\"')
			i = extend_quotes(str, i, lst, extend_v);
	}
	else if (str[i] == '$' && extend_v)
		i = extend_var(str, i, lst);
	return (i);
}

/*
* ft_extend est une fonction qui enleve les guillemets de type ' et "
* et remplace le nom des variables d'environnement par leurs valeurs
*/
char	*ft_extend(char *str, int extend_v, int extend_q, int heredoc)
{
	t_list	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		i += join_normal(str + i, &lst, extend_v, heredoc);
		i += expand_and_join(str + i, &lst, extend_v, extend_q);
	}
	free(str);
	return (ft_lstjoin(lst));
}
