/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:53:32 by adesvall          #+#    #+#             */
/*   Updated: 2021/10/10 19:01:46 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef union u_dir
{
    char *file;
    int pipe;
}               t_dir;

typedef struct s_proc
{
    char    *command;
    t_dir   dir_in;
    t_dir   dir_out;
    
}               t_proc;

void    skip_quotes(char *line, int *i)
{
    char c;

    if (line[*i] != '\'' && line[*i] != '"')
        return ;
    c = line[*i];
    *i++;
    while (line[*i] != c)
        *i++;
    *i++;
}

char **split_process(char *line)
{
    char **res;
    int i;

    i = 0;
    while (line[i])
    {
        skip_quotes(line, &i);
        if (line[i] == '|')
            line[i] = '\n';
        i++;
    }
    return (ft_split(line, '\n'));
}

int parse_line(char *line)
{
    char *processes;

    processes = split_process(line);
    

    return (0);
}