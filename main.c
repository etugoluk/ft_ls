#include "ft_ls.h"

int main(void) {
	t_ls ls;

	ls.d = opendir(".");
	if (ls.d) {
	while ((ls.dir = readdir(ls.d)) != NULL)
	{
		ft_printf("%s\n", ls.dir->d_name);
	}
	closedir(ls.d);
	}
	return(0);
}
