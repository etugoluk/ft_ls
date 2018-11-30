#include "ft_ls.h"

void	full_info(t_lst *file, char *dname)
{
	struct stat buf;

	char *tmpname = ft_strjoin(dname, ft_strjoin("/", file->name));
	stat(tmpname, &buf);
	file->rights[0] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	file->rights[1] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	file->rights[2] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
	file->rights[3] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	file->rights[4] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	file->rights[5] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
	file->rights[6] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	file->rights[7] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	file->rights[8] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	file->rights[9] = '\0';

	file->links = buf.st_nlink;

	struct passwd *pw = getpwuid(buf.st_uid);
	struct group  *gr = getgrgid(buf.st_gid);

	file->pw_name = (pw) ? pw->pw_name : NULL;
	file->gr_name = (gr) ? gr->gr_name : NULL;

	file->size = buf.st_size;
	char *tmp = ctime(&buf.st_mtime);
	file->mtime = buf.st_mtime;
	file->time = ft_strsub(tmp, 4, ft_strlen(tmp) - 5);

	// int i = 4;
	// while (i < 16)
	// {
	// 	ft_putchar(time[i++]);
	// }
	// ft_putchar(' ');
}

void	get_files(t_dir *d, t_ls *ls)
{
	struct s_lst *tmp_files = NULL;

	if ((ls->dir = readdir(d->dir_name)))
	{
		d->files = (t_lst *)malloc(sizeof(t_lst));
		d->files->name = ft_strdup(ls->dir->d_name);
		d->files->type = ls->dir->d_type;
		full_info(d->files, d->str_name);
		d->files->next = NULL;
		tmp_files = d->files;
	}
	while ((ls->dir = readdir(d->dir_name)))
	{
		d->files->next = (t_lst *)malloc(sizeof(t_lst));
		d->files->next->name = ft_strdup(ls->dir->d_name);
		d->files->next->type = ls->dir->d_type;
		full_info(d->files->next, d->str_name);
		d->files->next->next = NULL;
		d->files = d->files->next;
	}
	d->files = tmp_files;
}
