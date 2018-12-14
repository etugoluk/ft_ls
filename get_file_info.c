#include "ft_ls.h"

char*	get_color(char type, char *rights)
{
	if (type == DT_DIR)
		return "[34m";
	else if (type == DT_LNK)
		return "[35m";
	else if ((type == DT_BLK) || (type == DT_CHR))
		return "[33m";
	else if (ft_strchr(rights, 'x'))
		return "[31m";
	else
		return "[0m";
}

char*	full_name(char *dname, char *fname)
{
	size_t size = ft_strlen(dname) + ft_strlen(fname) + 1;
	char *tmpname = (char *)malloc(sizeof(char) * (size + 1));
	size_t i = 0;
	while (i < size)
	{
		if (i < ft_strlen(dname))
			tmpname[i] = dname[i];
		else if (i == ft_strlen(dname))
			tmpname[i] = '/';
		else
			tmpname[i] = fname[i - 1 - ft_strlen(dname)];
		i++;
	}
	tmpname[size] = '\0';
	return tmpname;
}

void	full_info(t_lst *file, char *dname, long *total, t_ls *ls, int *max, size_t *max_name, int *count)
{
	struct stat buf;

	char *tmpname = full_name(dname, file->name);

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

	if (listxattr(tmpname, NULL, 0, XATTR_NOFOLLOW))
		file->rights[9] = '@';
	else
		file->rights[9] = '\0';
	file->rights[10] = '\0'; //maybe better solution?

	file->links = buf.st_nlink;

	struct passwd *pw = getpwuid(buf.st_uid);
	struct group  *gr = getgrgid(buf.st_gid);

	file->pw_name = (pw) ? pw->pw_name : NULL;
	file->gr_name = (gr) ? gr->gr_name : NULL;

	file->size = buf.st_size;
	int digits = digitsu(file->size);
	if (digits > *max)
		*max = digits;

	char *tmp = ctime(&buf.st_mtime);
	file->mtime = buf.st_mtime;
	file->time = ft_strsub(tmp, 4, 12);

	if (file->name[0] != '.' || (ls->a_flag))
	{
		*total += buf.st_blocks;
		(*count)++;
	}

	file->color = (ls->G_flag) ? get_color(file->type, file->rights) : "[0m";

	size_t size_name = ft_strlen(file->name);
	if (size_name > *max_name)
		*max_name = size_name; 

	free(tmpname);
}

long	get_files(t_dir *d, t_ls *ls)
{
	struct s_lst	*tmp_files = NULL;
	long			total = 0;
	int				max = 0;
	size_t			max_name = 0;

	d->count = 0;
	if ((ls->dir = readdir(d->dir_name)))
	{
		d->files = (t_lst *)malloc(sizeof(t_lst));
		d->files->name = ft_strdup(ls->dir->d_name);
		d->files->type = ls->dir->d_type;
		full_info(d->files, d->str_name, &total, ls, &max, &max_name, &d->count);
		d->files->next = NULL;
		tmp_files = d->files;
	}
	while ((ls->dir = readdir(d->dir_name)))
	{
		d->files->next = (t_lst *)malloc(sizeof(t_lst));
		d->files->next->name = ft_strdup(ls->dir->d_name);
		d->files->next->type = ls->dir->d_type;
		full_info(d->files->next, d->str_name, &total, ls, &max, &max_name, &d->count);
		d->files->next->next = NULL;
		d->files = d->files->next;
	}
	d->files = tmp_files;
	d->digits_max = max;
	d->name_max = max_name;
	return total;
}
