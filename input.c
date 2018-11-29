#include "ft_ls.h"

void	get_files(t_dir *d, t_ls *ls)
{
	struct s_lst *tmp_files = NULL;

	if ((ls->dir = readdir(d->dir_name)))
	{
		d->files = (t_lst *)malloc(sizeof(t_lst));
		d->files->name = ft_strdup(ls->dir->d_name);
		d->files->next = NULL;
		tmp_files = d->files;
	}
	while ((ls->dir = readdir(d->dir_name)))
	{
		d->files->next = (t_lst *)malloc(sizeof(t_lst));
		d->files->next->name = ft_strdup(ls->dir->d_name);
		d->files->next->next = NULL;
		d->files = d->files->next;
	}
	d->files = tmp_files;
}

void	new_dir(char *str, t_ls *ls)
{
	if (!ls->d)
	{
		ls->d = (t_dir *)malloc(sizeof(t_dir));
		if (!(ls->d->dir_name = opendir(str)))
		{
			ft_printf("ft_ls: %s: %s\n", str, strerror(errno));
			free(ls->d);
			ls->d = NULL;
			return ;
		}
		ls->d->str_name = ft_strdup(str);
		get_files(ls->d, ls);
		ls->d->next = NULL;
		return ;
	}
	struct s_dir *tmp = ls->d;
	while (ls->d->next)
		ls->d = ls->d->next;
	ls->d->next = (t_dir *)malloc(sizeof(t_dir));
	if (!(ls->d->next->dir_name = opendir(str)))
	{
		ft_printf("ft_ls: %s: %s\n", str, strerror(errno));
		free(ls->d->next);
		ls->d->next = NULL;
		return ;
	}
	ls->d->next->str_name = ft_strdup(str);
	get_files(ls->d->next, ls);
	ls->d->next->next = NULL;
	ls->d = tmp;
}

void	new_flag(char *str, t_ls *ls)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'l')
			ls->l_flag = 1;
		else if (str[i] == 'R')
			ls->R_flag = 1;
		else if (str[i] == 'a')
			ls->a_flag = 1;
		else if (str[i] == 'r')
			ls->r_flag = 1;
		else if (str[i] == 't')
			ls->t_flag = 1;
		else
		{
			ft_printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			return ;
		}
		i++;
	}
}
