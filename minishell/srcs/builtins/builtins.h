/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:34:47 by user42            #+#    #+#             */
/*   Updated: 2022/01/08 12:11:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include "../../libft/libft.h"

typedef struct s_var	t_var;

struct s_var
{
	char	*name;
	char	*value;
	t_var	*next;
};

int		ft_cd(char **args, t_var *env); // OK
int		ft_echo(char **args); // OK
int		ft_env(char **args, t_var *env); // OK
int		ft_export(char **args, t_var **envp); // OK
int		ft_pwd(char **args, t_var *env); // a discuter
int		ft_unset(char **args, t_var **envp); // OK

void	destroy_var(t_var *var);
void	clear_env(t_var **list);
t_var	*malloc_var(char *name, char *value);
void	add_var(t_var **env, char *name, char *value);
t_var	*load_env(char **args);
char	**unload_env(t_var *env);
int		env_size(t_var *env);
char	*get_var(t_var *env, char *name);
int		check_var_name(char *name);

int	check_var_value(char *name);
void	sort_tab(t_var	**tab);
t_var	**get_tab(t_var *env);
int	export_sort(t_var *env);


#endif
