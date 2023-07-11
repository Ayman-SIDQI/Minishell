/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:17:03 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/06 17:05:06 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdio.h>

t_stack	*ft_lstnew(char *str, short type)
{
	t_stack	*list;

	if (!str)
		return (NULL);
	list = malloc(sizeof(t_stack));
	if (!list)
		return (0);
	list->content = ft_strdup(str);
	list->type = type;
	list->next = 0;
	return (list);
}
