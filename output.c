#include "ft_ls.h"

void	print(t_ls *ls)
{
	while (ls->d && ls->d->dir_name)
	{
		ft_printf("%s:\n", ls->d->str_name);
		while (ls->d->files)
		{
			ft_printf("%s\n", ls->d->files->name);
			ls->d->files = ls->d->files->next;
		}
		ls->d = ls->d->next;
		if (ls->d)
			ft_printf("\n");
		// closedir(ls.d);
	}
}
