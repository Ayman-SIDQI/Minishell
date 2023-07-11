/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:18:20 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/15 16:44:52 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	set_double(char **amal, int *i, char *line, t_stack *token)
{
	*amal = ft_strjoin(*amal, '"');
	(*i)++;
	while (line[*i] != '"')
	{
		if (line[*i] == '$' && line[*i + 1] != '$' && chfh(ft_lstlast(token)))
		{
			if (line[*i + 1] == '?')
				expandstatus(amal, i);
			else
				expandnormal (amal, i, line);
		}
		else if (line[*i] != '"')
		{
			*amal = ft_strjoin(*amal, line[*i]);
			(*i)++;
		}
	}
	*amal = ft_strjoin(*amal, line[*i]);
	(*i)++;
}

void	set_single(char **amal, int *i, char *line)
{
	*amal = ft_strjoin(*amal, '\'');
	(*i)++;
	while (line[*i] != '\'')
	{
		*amal = ft_strjoin(*amal, line[*i]);
		(*i)++;
	}
	*amal = ft_strjoin(*amal, '\'');
	(*i)++;
}

void	set_aadi(char **amal, int *i, char *line, t_stack **tokens)
{
	while (line[*i] != '|' && line[*i] != ' ' && line[*i] != '>' && \
	line[*i] != '<' && line[*i] != '"' && line[*i] != '\'' \
	&& line[*i] != '\0' && line[*i] != '\t')
	{
		if (line[*i] == '$' && line[*i + 1] != '$' && chfh(ft_lstlast(*tokens)))
		{
			if (line[*i + 1] == '?')
				expandstatus(amal, i);
			else
				expandwithtokens(amal, i, line, tokens);
		}
		else if (line[*i] != ' ' && line[*i])
		{
			*amal = ft_strjoin(*amal, line[*i]);
			(*i)++;
		}
	}
}

void	set_right(char **amal, int *i, char *commands, t_stack **tokens)
{
	if (commands[*i + 1] == '>')
	{
		(*amal) = ft_strjoin(*amal, '>');
		(*amal) = ft_strjoin(*amal, '>');
		*i += 2;
		ft_lstadd_back(tokens, ft_lstnew((*amal), APPEND));
		(*amal)[0] = '\0';
	}
	else
	{
		(*amal) = ft_strjoin(*amal, '>');
		(*i)++;
		ft_lstadd_back(tokens, ft_lstnew((*amal), LIMN));
		(*amal)[0] = '\0';
	}
}

void	set_left(char **amal, int *i, char *commands, t_stack **tokens)
{
	if (commands[*i + 1] == '<')
	{
		(*amal) = ft_strjoin(*amal, '<');
		(*amal) = ft_strjoin(*amal, '<');
		*i += 2;
		ft_lstadd_back(tokens, ft_lstnew((*amal), HEREDOC));
		(*amal)[0] = '\0';
	}
	else
	{
		(*amal) = ft_strjoin(*amal, '<');
		(*i)++;
		ft_lstadd_back(tokens, ft_lstnew((*amal), LISR));
		(*amal)[0] = '\0';
	}
}
