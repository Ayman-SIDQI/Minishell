/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seters.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:26:47 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/12 14:27:27 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_type(t_stack *tokens)
{
	int		i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			i = 1;
		else if (tokens->type == HEREDOC)
			tokens->next->type = HER_ARG;
		else if (tokens->type == NONE && i)
		{
			i = 0;
			tokens->type = CMD;
		}
		else if (tokens->type == NONE && !i)
			tokens->type = ARG;
		else if (tokens->type == LIMN || tokens->type == APPEND)
			tokens->next->type = IN_FILE;
		else if (tokens->type == LISR)
			tokens->next->type = OUT_FILE;
		tokens = tokens->next;
	}
}

void	set_double2(char **amal, int *i, char *line)
{
	(*i)++;
	while (line[*i] != '"')
	{
		*amal = ft_strjoin(*amal, line[*i]);
		(*i)++;
	}
}

void	set_single2(char **amal, int *i, char *line)
{
	(*i)++;
	while (line[*i] != '\'')
	{
		*amal = ft_strjoin(*amal, line[*i]);
		(*i)++;
	}
}
