/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcharia < hcharia@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:54:37 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/16 11:33:04 by hcharia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_variables_lexer(int *i, char **amal, t_stack **tokens)
{
	*i = 0;
	*amal = (char *)malloc(sizeof(char));
	if (!*amal)
		exit (1);
	*amal[0] = '\0';
	*tokens = NULL;
}

int	lexer(char *commands, t_stack **tokens)
{
	int		i;
	int		j;
	char	*amal;

	set_variables_lexer(&i, &amal, tokens);
	while (commands[i])
	{
		skip_space(&i, commands);
		while (delimiters(commands[i]))
		{
			if (delimiters(commands[i]) && commands[i] != ' ')
			{
				j = set_amal_adi(commands, &i, &amal, tokens);
				if (j == 1)
					break ;
				else if (j == -1)
					return (free(amal), freet_stack(tokens), \
						printf("%s\n", SYNT), g_struct->ex_st = 1, \
						free(commands), 0);
			}
		}
		set_delimiters(&amal, tokens, commands, &i);
	}
	return (free(commands), free(amal), 1);
}
