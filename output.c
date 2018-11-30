#include "ft_ls.h"

void	print(t_ls *ls)
{
	int k;

	k = (ls->d->next) ? 1 : 0;
	while (ls->d && ls->d->dir_name)
	{
		if (k)
			ft_printf("%s:\n", ls->d->str_name);
		while (ls->d->files)
		{
			if (ls->d->files->name[0] != '.' || (ls->a_flag))
			{
				if (ls->l_flag)
					ft_printf("%s %3ld %s %s %6lld %s ", ls->d->files->rights, ls->d->files->links,
						ls->d->files->pw_name, ls->d->files->gr_name, ls->d->files->size, ls->d->files->time);
				ft_printf("%s\n", ls->d->files->name);
			}
			ls->d->files = ls->d->files->next;
		}
		ls->d = ls->d->next;
		if (ls->d)
			ft_printf("\n");
		// closedir(ls.d);
	}
}
