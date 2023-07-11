/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asidqi <asidqi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:48:27 by asidqi            #+#    #+#             */
/*   Updated: 2023/06/17 00:21:17 by asidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iszerostring(char *c)
{
	int	i;

	i = 0;
	if ((c[i] == '+') || (c[i] == '-'))
		i++;
	while (c[i] == '0')
		i++;
	if (c[i] == '\0')
		return (1);
	return (0);
}

int	ft_strcmp1(char *s1, char *s2)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	if (s1[i] == '-' && s1[i + 1] == '0' && ft_iszerostring((char *)s1))
		i++;
	else if (s1[i] == '-' && s1[i + 1] == '0')
	{
		i++;
		o++;
	}
	while (s1[i] == '+')
		i++;
	while (s1[i + 1] && s1[i] == '0')
		i++;
	while ((s1[i] != '\0' || s2[o] != '\0'))
	{
		if (s1[i] != s2[o])
			return ((unsigned char)s1[i] - (unsigned char)s2[o]);
		i++;
		o++;
	}
	free(s2);
	return (0);
}

int	ft_isdigit2(char *c)
{
	int	i;

	i = 0;
	while ((c[i] >= '0' && c[i] <= '9') || (c[i] == '+') || (c[i] == '-'))
		i++;
	if (c[i] == '\0')
		return (0);
	return (1);
}

int	exit_status(char **args, int mode)
{
	if (doublelengh(args) > 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		g_struct->ex_st = 1;
		mode = 69;
		return (mode);
	}
	if ((ft_isdigit2(args[1])) \
	|| (ft_atoi(args[1]) == 0 && !ft_iszerostring(args[1])) \
	|| ft_strcmp1(args[1], ft_itoa(ft_atoi(args[1]))) \
	|| !(ft_atoi(args[1]) >= -2147483648 && ft_atoi(args[1]) <= 2147483647))
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_struct->ex_st = 255;
		return (mode);
	}
	if (mode != 69)
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(args[1]));
	}
	g_struct->ex_st = ft_atoi(args[1]);
	return (0);
}

void	builtin_exec(t_redir *redirs, short mode)
{
	if (ft_strcmp(redirs->refined_cmd[0], "pwd") == 0)
		pwd();
	else if ((ft_strcmp(redirs->refined_cmd[0], "exit") == 0) && mode == 69)
	{
		mode = -1;
		if (redirs->refined_cmd[1] && mode == 69)
			mode = exit_status(redirs->refined_cmd, 69);
		else if (redirs->refined_cmd[1] && mode != 69)
			mode = exit_status(redirs->refined_cmd, -1);
	}
	else if (ft_strcmp(redirs->refined_cmd[0], "export") == 0)
		export(&redirs->refined_cmd[1]);
	else if (ft_strcmp(redirs->refined_cmd[0], "echo") == 0)
		echo(redirs);
	else if (ft_strcmp(redirs->refined_cmd[0], "cd") == 0 && mode == 69)
		cd(redirs);
	else if (ft_strcmp(redirs->refined_cmd[0], "env") == 0)
		env();
	else if (ft_strcmp(redirs->refined_cmd[0], "unset") == 0)
		unset(redirs->refined_cmd);
	if (mode != 69)
		g_struct->exited = 0;
	return ;
}
