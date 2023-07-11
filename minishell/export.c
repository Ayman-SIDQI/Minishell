/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:54:40 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/17 00:17:40 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*thebefeq(char *s)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(1);
	res[0] = '\0';
	while (s[i] && s[i] != '=')
	{
		res = ft_strjoin(res, s[i]);
		i++;
	}
	return (res);
}

t_stack	*search_node_delete(t_stack **head, char *element)
{
	t_stack	*temp;
	char	*s;

	temp = *head;
	while (temp != NULL)
	{
		s = thebefeq(temp->content);
		if (!ft_strcmp(s, element))
		{
			free (s);
			break ;
		}
		temp = temp->next;
		free (s);
	}
	return (temp);
}

void	deletenode(t_stack **head, char *element)
{
	t_stack	*temp;

	if (head == NULL || *head == NULL || element == NULL)
		return ;
	temp = search_node_delete(head, element);
	if (temp == NULL)
		return ;
	if (temp == *head)
	{
		*head = temp->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		free (temp->content);
		free (temp);
		return ;
	}
	if (temp->prev != NULL)
		temp->prev->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = temp->prev;
	free (temp->content);
	free(temp);
}

int	checkexarg(char *v)
{
	int	i;

	i = 0;
	if (v[0] != '_' && !ft_isalpha(v[0]))
		return (0);
	while (v[i] && v[i] != '=')
	{
		if (v[i] != '_' && !ft_isalnum(v[i]))
			return (0);
		i++;
	}
	return (1);
}

int	checkequal(char *v)
{
	int	i;

	i = 0;
	while (v[i])
	{
		if (v[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
