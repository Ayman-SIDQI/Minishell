/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:45:32 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/12 12:59:02 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*tmp;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = ft_lstlast (*lst);
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}

int	delimiters(char c)
{
	if (c != '|' && c != '>' && c != '<' && c != '\0')
		return (1);
	return (0);
}

int	delimiters2(char c)
{
	if (c == '\0' || c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	set_amal_adi(char *commands, int *i, char **amal, t_stack **tokens)
{
	if (commands[*i] == '\"')
	{
		if (closing_quote(commands, *i, '\"') == -1)
			return (-1);
		set_double(amal, i, commands, *tokens);
	}
	else if (commands[*i] == '\'')
	{
		if (closing_quote(commands, *i, '\'') == -1)
			return (-1);
		set_single(amal, i, commands);
	}
	else
		set_aadi(amal, i, commands, tokens);
	if (delimiters2(commands[*i]))
		return (1);
	return (0);
}

void	set_delimiters(char **amal, t_stack **tokens, char *commands, int *i)
{
	if (*amal[0])
	{
		ft_lstadd_back(tokens, ft_lstnew(*amal, NONE));
		*amal[0] = '\0';
	}
	if (commands[*i] == '>')
		set_right(amal, i, commands, tokens);
	else if (commands[*i] == '<')
		set_left(amal, i, commands, tokens);
	else if (commands[*i] == '|')
		set_pipe(amal, i, tokens);
}
