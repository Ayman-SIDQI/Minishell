/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:37:54 by hcharia           #+#    #+#             */
/*   Updated: 2023/05/30 22:56:54 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

/*
	+-=	i9dr ikon mochkil f t_stack may3rfhach. Then put it back to lexer 
*/
void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*tmp;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*lst = new;
		new->prev = NULL;
	}
}
