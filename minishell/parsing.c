/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:27:59 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/17 00:05:42 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chfh2(t_stack *token)
{
	if (!token)
		return (1);
	if (token->prev)
	{
		if (token->prev->type == HEREDOC)
			return (0);
	}
	return (1);
}

int	piping_err(t_stack *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE && (!tokens->next || !tokens->prev))
			return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
		if (tokens->next)
		{
			if ((tokens->type == PIPE || tokens->type == LIMN || \
				tokens->type == LISR || tokens->type == HEREDOC || \
				tokens->type == APPEND) && tokens->next->type == PIPE)
				return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	limnlisr(t_stack *element)
{
	if (element->type == LIMN || element->type == LISR)
		return (1);
	return (0);
}

int	appherd(t_stack *element)
{
	if (element->type == APPEND || element->type == HEREDOC)
		return (1);
	return (0);
}

int	redirection_err(t_stack *tokens)
{
	while (tokens)
	{
		if ((limnlisr(tokens) || appherd(tokens)) && !tokens->next)
			return (g_struct->ex_st = 1, printf("%s\n", SYNT), 2);
		if (tokens->next)
		{
			if (tokens->type == LISR && tokens->next->type == LIMN)
			{
				if (tokens->next->next)
					if (tokens->next->next->type != NONE)
						return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
			}
			else if (limnlisr (tokens) && tokens->next->type == LISR)
				return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
			else if (appherd(tokens) && tokens->next->type == LISR)
				return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
			else if (appherd(tokens) && tokens->next->type == LIMN)
				return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
			else if (appherd(tokens) && appherd(tokens->next))
				return (g_struct->ex_st = 1, printf("%s\n", SYNT), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}
