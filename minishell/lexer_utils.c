/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:21:12 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/11 17:55:46 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	skip_space(int *i, char *commands)
{
	while (commands[*i] == ' ' || commands[*i] == '\t')
		(*i)++;
}

short	closing_quote(char *line, int i, short quote)
{
	char	s;

	if (quote == SINGLE_Q)
		s = '\'';
	else
		s = '"';
	i++;
	while (line[i])
	{
		if (line[i] == s)
			return (quote);
		i++;
	}
	return (-1);
}

void	set_pipe(char **amal, int *i, t_stack **tokens)
{
	(*amal) = ft_strjoin(*amal, '|');
	(*i)++;
	ft_lstadd_back(tokens, ft_lstnew((*amal), PIPE));
	(*amal)[0] = '\0';
}
