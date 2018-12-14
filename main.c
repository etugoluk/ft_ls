#include "ft_ls.h"

void	init(t_ls *ls)
{
	ls->d = NULL;
	ls->dir = NULL;

	ls->l_flag = 0;
	ls->R_flag = 0;
	ls->a_flag = 0;
	ls->r_flag = 0;
	ls->t_flag = 0;
	ls->f_flag = 0;
	ls->G_flag = 0;
	ls->u_flag = 0;
	ls->col_flag = 0;

	ls->reg_flag = 0;
	ls->dir_flag = 0;
	ls->link_flag = 0;
}

int		main(int argc, char **argv)
{
	t_ls ls;
	int i;

	i = 1;
	init(&ls);

	while (i < argc && argv[i][0] == '-')
		new_flag(argv[i++], &ls);

	if (i >= argc)
		new_dir(".", &ls);
	else
		while (i < argc && argv[i])
			new_dir(argv[i++], &ls);

	if (!ls.d)
		return (0);
	if (ls.t_flag)
		sort_list(ls.d->files, desc_time);
	else if (!ls.f_flag)
		(ls.r_flag) ? sort_list(ls.d->files, asc) : sort_list(ls.d->files, desc);
	print(&ls);
	// system("leaks ft_ls");
	return (0);
}
