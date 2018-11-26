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
}

int		main(int argc, char **argv) {
	t_ls ls;

	init(&ls);
	if (argc == 1)
		new_dir(".", &ls);
	else
	{
		read_flags_and_dirs(argc, argv, &ls);
		if (!ls.d)
			new_dir(".", &ls);
	}
	write_to_list(&ls);
	sort_list(ls.d->files);
	print(&ls);
	return (0);
}
