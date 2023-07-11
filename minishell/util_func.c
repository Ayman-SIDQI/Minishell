/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:14:33 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/04 15:09:49 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**link_toarr(t_stack *tokens)
{
	int		count;
	char	**array;
	int		i;

	i = 0;
	count = ft_lstsize(tokens);
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (tokens)
	{
		array[i] = ft_strdup(tokens->content);
		tokens = tokens->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	len;
	char	*ret;

	i = 0;
	len = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	while (s1[len])
	{
		ret[len] = s1[len];
		len++;
	}
	while (s2[i])
		ret[len++] = s2[i++];
	ret[len] = '\0';
	free (s1);
	return (ret);
}
