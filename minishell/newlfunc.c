/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 22:34:32 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/12 13:06:54 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*lstlast_redir(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_redir	*lstnew_redir(void)
{
	t_redir	*list;

	list = malloc(sizeof(t_redir));
	if (!list)
		return (0);
	list->next = 0;
	return (list);
}

void	lstadd_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = lstlast_redir (*lst);
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}

t_redir	*creat_cmdlist(int pipe_c)
{
	int		node_c;
	int		i;
	t_redir	*list;
	t_redir	*node;

	node_c = pipe_c + 1;
	i = 0;
	list = NULL;
	while (i < node_c)
	{
		node = lstnew_redir();
		lstadd_redir(&list, node);
		i++;
	}
	return (list);
}

int	chfh(t_stack *token)
{
	if (!token)
		return (1);
	if (token->type == HEREDOC)
		return (0);
	return (1);
}
