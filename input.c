#include "ft_ls.h"

char	get_type(char *file)
{
	struct stat buf;

	stat(file, &buf);
	if (S_ISREG(buf.st_mode))
		return ('-');
	else if (S_ISDIR(buf.st_mode))
		return ('d');
	else if (S_ISCHR(buf.st_mode))
		return ('c');
	else if (S_ISBLK(buf.st_mode))
		return ('b');
	else if (S_ISFIFO(buf.st_mode))
		return ('p');
	else if (S_ISLNK(buf.st_mode))
		return ('l');
	else if (S_ISSOCK(buf.st_mode))
		return ('s');
	return (0);
}

void	get_files(t_dir *d, t_ls *ls)
{
	struct s_lst *tmp_files = NULL;

	if ((ls->dir = readdir(d->dir_name)))
	{
		d->files = (t_lst *)malloc(sizeof(t_lst));
		d->files->name = ft_strdup(ls->dir->d_name);
		d->files->type = ls->dir->d_type;
		d->files->next = NULL;
		tmp_files = d->files;
	}
	while ((ls->dir = readdir(d->dir_name)))
	{
		d->files->next = (t_lst *)malloc(sizeof(t_lst));
		d->files->next->name = ft_strdup(ls->dir->d_name);
		d->files->next->type = ls->dir->d_type;
		d->files->next->next = NULL;
		d->files = d->files->next;
	}
	d->files = tmp_files;
}

void	recursive(t_lst	*files, t_ls *ls, char *dname)
{
	t_lst	*tmp = files;
	while (files)
	{
		if (files->type == 4 && ft_strcmp(files->name,".") && ft_strcmp(files->name,".."))
		{
			if (files->name[0] == '.' && !ls->a_flag)
			{
				files = files->next;
				continue;
			}
			char *tmpname = ft_strjoin(dname, ft_strjoin("/", files->name));
			new_dir(tmpname, ls);
//			new_dir(files->name, ls);
		}
		files = files->next;
	}
	files = tmp;
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
		if (ls->R_flag)
			recursive(ls->d->files, ls, ls->d->str_name);
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
	if (ls->R_flag)
		recursive(ls->d->next->files, ls, ls->d->next->str_name);
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
