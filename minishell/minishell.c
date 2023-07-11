/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:19:59 by hcharia           #+#    #+#             */
/*   Updated: 2023/06/16 23:17:57 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_struct;

char	**twodimension_dup(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (envp[++i])
		new[i] = ft_strdup(envp[i]);
	new[i] = NULL;
	return (new);
}

short	uncalledfor(void)
{
	if (getenv("PATH") == NULL)
	{
		printf("Dear evaluator... \nthis shouldn't work with env -i in our case ecause the way to handle it is to manually add the session's \
		path which is a bullsh*t solution because it simply won't work in \
		 other sessions\n");
		return (1);
	}
	return (0);
}

int	main_start(char **envp, int c, char **v)
{
	if (uncalledfor())
		return (0);
	init_gstruct(envp, c, v);
	if (sig_func())
		return (0);
	return (1);
}

int	main(int c, char **v, char *envp[])
{
	char				*line;
	t_stack				*tokens;

	if (!main_start(envp, c, v))
		return (1);
	while (g_struct->exited)
	{
		line = readline ("> ");
		if (line == NULL)
		{
			ctrl_d();
			continue ;
		}
		if (*line)
			add_history(line);
		if (!lexer(line, &tokens))
			continue ;
		if (!tokens || !parsing(&tokens) || single(tokens))
			continue ;
		arch_exec(tokens);
		g_struct->h_sigy = 0;
	}
	return (g_struct->ex_st);
}
