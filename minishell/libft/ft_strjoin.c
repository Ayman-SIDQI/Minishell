/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:08:47 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/12 13:03:14 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char c)
{
	char	*s;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	s = malloc(len + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = c;
	s[i + 1] = '\0';
	free (s1);
	s1 = NULL;
	return (s);
}
