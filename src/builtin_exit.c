/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 10:38:09 by dchief            #+#    #+#             */
/*   Updated: 2020/11/15 02:07:58 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

static int		g_owerflow;

static int		get_num(const char *str)
{
	int			i;
	long int	tmp;

	i = 0;
	tmp = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			tmp = tmp * 10 + str[i] - '0';
			if (tmp < 0)
			{
				g_owerflow = 1;
				return (-1);
			}
			i++;
		}
		else
			break ;
	}
	return (tmp);
}

static int		atoi_exit(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	num = get_num(str);
	if (!g_owerflow)
		num *= sign;
	return (num);
}

static int		is_alldigit(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		if ((s[0] == '-') || (s[0] == '+'))
			i++;
		while (s[i] && ft_isdigit(s[i]))
			i++;
		if (!s[i])
			return (1);
	}
	return (0);
}

int				ft_exit(t_ex *ex)
{
	long int	exit_code;
	int			i;

	if ((ex->process.argc > 2) && (is_alldigit(ex->process.argv[1])))
		ft_putendl_fd("exit: too many arguments", 2);
	else
	{
		exit_code = 0;
		i = 0;
		while (ex->pipeline->child && (ex->pipeline->child)[i])
			i++;
		if (ex->process.argc > 1)
			exit_code = is_alldigit(ex->process.argv[1]) ?
			atoi_exit(ex->process.argv[1]) : -1;
		if (ex->process.argv[1] &&
		(!is_alldigit(ex->process.argv[1]) || g_owerflow))
			print_err("exit", ex->process.argv[1], "numeric argument required");
		if (i == 1)
		{
			ft_putendl_fd("exit", 2);
			exit_code < 0 ? exit(256 + exit_code % 256) : exit(exit_code % 256);
		}
	}
	return (1);
}
