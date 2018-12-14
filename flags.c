/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 18:17:27 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 18:17:31 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		bonus_flag(char *str, t_ls *ls)
{
	if (!ft_strcmp(str, "--dir"))
	{
		ls->dir_flag = 1;
		return (1);
	}
	else if (!ft_strcmp(str, "--reg"))
	{
		ls->reg_flag = 1;
		return (1);
	}
	else if (!ft_strcmp(str, "--link"))
	{
		ls->link_flag = 1;
		return (1);
	}
	return (0);
}

int		set_flags(char *str, int i, t_ls *ls)
{
	if ((str[i] > 48) && (str[i] < 53) && (!ft_strchr(str, 'l')))
		ls->col_flag = str[i] - 48;
	else if (str[i] == 'l')
		ls->l_flag = 1;
	else if (str[i] == 'R')
		ls->R_flag = 1;
	else if (str[i] == 'a')
		ls->a_flag = 1;
	else if (str[i] == 'r')
		ls->r_flag = 1;
	else if (str[i] == 't')
		ls->t_flag = 1;
	else if (str[i] == 'G')
		ls->G_flag = 1;
	else if (str[i] == 'u')
		ls->u_flag = 1;
	else if (str[i] == 'f')
	{
		ls->f_flag = 1;
		ls->a_flag = 1;
	}
	else
		return (0);
	return (1);
}

void	new_flag(char *str, t_ls *ls)
{
	int i;

	if (bonus_flag(str, ls))
		return ;
	i = 1;
	while (str[i])
	{
		if (!set_flags(str, i, ls))
		{
			ft_printf("----------------------------------------------------------\n");
			ft_printf("usage: ls [-afGlnrRtu] [--dir] [--reg] [--link] [file ...]\n");
			ft_printf("n - number of columns (from 1 to 4)\n");
			ft_printf("--dir - show only directories\n");
			ft_printf("--reg - show only regular files\n");
			ft_printf("--link - show only links\n");
			ft_printf("----------------------------------------------------------\n");
			return ;
		}
		i++;
	}
}
