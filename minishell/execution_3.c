/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:37:06 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/16 21:38:57 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	pipe_counter(t_stack *tokens)
{
	size_t	i;
	t_stack	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	fill_refined(t_stack **temp, char **refined_cmd)
{
	int	i;

	i = 0;
	while ((*temp) && (*temp)->type != PIPE)
	{
		if ((*temp)->type == CMD || (*temp)->type == ARG)
		{
			refined_cmd[i] = ft_strdup((*temp)->content);
			i++;
		}
		(*temp) = (*temp)->next;
	}
}

char	**refine(t_stack *tokens)
{
	int			i;
	char		**refined_cmd;
	t_stack		*temp;

	i = 0;
	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == CMD || temp->type == ARG)
			i++;
		temp = temp->next;
	}
	refined_cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!refined_cmd)
		return (NULL);
	temp = tokens;
	fill_refined(&temp, refined_cmd);
	refined_cmd[i] = NULL;
	return (refined_cmd);
}
