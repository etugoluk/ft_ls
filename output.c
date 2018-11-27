#include "ft_ls.h"

void	get_info(char *file)
{
	struct stat buf;

	stat(file, &buf);
	if (S_ISREG(buf.st_mode))
		ft_printf("-");
	else if (S_ISDIR(buf.st_mode))
		ft_printf("d");
	else if (S_ISCHR(buf.st_mode))
		ft_printf("c");
	else if (S_ISBLK(buf.st_mode))
		ft_printf("b");
	else if (S_ISFIFO(buf.st_mode))
		ft_printf("p");
	else if (S_ISLNK(buf.st_mode))
		ft_printf("l");
	else if (S_ISSOCK(buf.st_mode))
		ft_printf("s");

	ft_printf( (buf.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (buf.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (buf.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (buf.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (buf.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (buf.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (buf.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (buf.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (buf.st_mode & S_IXOTH) ? "x " : "- ");
    ft_printf(" %3ld ", (long) buf.st_nlink);

    struct passwd *pw = getpwuid(buf.st_uid);
	struct group  *gr = getgrgid(buf.st_gid);
	ft_printf("%s  %s ", pw->pw_name, gr->gr_name);
	ft_printf("%6lld ", (long long) buf.st_size);
	char* time = ctime(&buf.st_mtime);
	int i = 4;
	while (i < 16)
	{
		ft_putchar(time[i++]);
	}
	ft_putchar(' ');
}

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
				get_info(ls->d->files->name);
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
