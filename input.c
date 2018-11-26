#include "ft_ls.h"

void	new_dir(char *str, t_ls *ls)
{
	if (!ls->d)
	{
		ls->d = (t_dir *)malloc(sizeof(t_dir));
		ls->d->dir_name = opendir(str);
		ls->d->str_name = ft_strdup(str);
		ls->d->files = NULL;
		ls->d->next = NULL;
		return ;
	}
	while (ls->d->next)
		ls->d = ls->d->next;
	ls->d->next = (t_dir *)malloc(sizeof(t_dir));
	ls->d->next->dir_name = opendir(str);
	ls->d->next->str_name = ft_strdup(str);
	ls->d->next->files = NULL;
	ls->d->next->next = NULL;
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

void	read_flags_and_dirs(int argc, char **argv, t_ls *ls)
{
	int i;

	i = 1;
	while (i < argc && argv[i][0] == '-')
		new_flag(argv[i++], ls);
	while (i < argc && argv[i])
		new_dir(argv[i++], ls);
}

void	write_to_list(t_ls *ls)
{
	struct s_dir *tmp_d = ls->d;
	struct s_lst *tmp_files = NULL;

	while (ls->d && ls->d->dir_name)
	{
		if ((ls->dir = readdir(ls->d->dir_name)))
		{
			ls->d->files = (t_lst *)malloc(sizeof(t_lst));
			ls->d->files->name = ft_strdup(ls->dir->d_name);
			ls->d->files->next = NULL;
			tmp_files = ls->d->files;
		}
		while ((ls->dir = readdir(ls->d->dir_name)))
		{
			ls->d->files->next = (t_lst *)malloc(sizeof(t_lst));
			ls->d->files->next->name = ft_strdup(ls->dir->d_name);
			ls->d->files->next->next = NULL;
			ls->d->files = ls->d->files->next;
		}
		ls->d->files = tmp_files;
		ls->d = ls->d->next;
	}
	ls->d = tmp_d;
}
