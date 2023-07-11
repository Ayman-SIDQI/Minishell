/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:25:13 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/12 13:03:02 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = -1;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (s1[++len] != '\0')
		ret[len] = s1[len];
	while (s2[i] != '\0')
		ret[len++] = s2[i++];
	ret[len] = '\0';
	free(s1);
	return (ret);
}
