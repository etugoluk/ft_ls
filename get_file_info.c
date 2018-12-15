/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:52:21 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 17:52:23 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_color(char type, char *rights)
{
	if (type == DT_DIR)
		return ("[34m");
	else if (type == DT_LNK)
		return ("[35m");
	else if ((type == DT_BLK) || (type == DT_CHR))
		return ("[33m");
	else if (ft_strchr(rights, 'x'))
		return ("[31m");
	else
		return ("[0m");
}

char	*full_name(char *dname, char *fname)
{
	size_t	size;
	char	*tmpname;
	size_t	i;

	size = ft_strlen(dname) + ft_strlen(fname) + 1;
	tmpname = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
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
	return (tmpname);
}

void	set_rights(t_lst *file, struct stat buf)
{
	struct passwd	*pw;
	struct group	*gr;

	file->rights[0] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	file->rights[1] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	file->rights[2] = (buf.st_mode & S_IXUSR) ? 'x' : '-';
	file->rights[3] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	file->rights[4] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	file->rights[5] = (buf.st_mode & S_IXGRP) ? 'x' : '-';
	file->rights[6] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	file->rights[7] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
	file->rights[8] = (buf.st_mode & S_IXOTH) ? 'x' : '-';
	file->rights[9] = (listxattr(file->full_name, NULL, 0,
						XATTR_NOFOLLOW)) ? '@' : '\0';
	file->rights[10] = '\0';
	file->links = buf.st_nlink;
	pw = getpwuid(buf.st_uid);
	gr = getgrgid(buf.st_gid);
	file->pw_name = (pw) ? pw->pw_name : NULL;
	file->gr_name = (gr) ? gr->gr_name : NULL;
	file->size = buf.st_size;
}

void	full_info(t_lst *file, t_dir *d, t_ls *ls)
{
	struct stat		buf;
	int				digits;
	char			*tmp;
	size_t			size_name;

	file->full_name = full_name(d->str_name, file->name);
	stat(file->full_name, &buf);
	set_rights(file, buf);
	digits = digitsu(file->size);
	if (digits > d->digits_max)
		d->digits_max = digits;
	tmp = (ls->u_flag) ? ctime(&buf.st_atime) : ctime(&buf.st_mtime);
	file->mtime = buf.st_mtime;
	file->time = ft_strsub(tmp, 4, 12);
	if (file->name[0] != '.' || (ls->a_flag))
	{
		d->block_size += buf.st_blocks;
		d->count++;
	}
	file->color = (ls->G_flag) ? get_color(file->type, file->rights) : "[0m";
	size_name = ft_strlen(file->name);
	if (size_name > d->name_max)
		d->name_max = size_name;
}

void	get_files(t_dir *d, t_ls *ls)
{
	struct s_lst	*tmp_files;

	d->block_size = 0;
	d->name_max = 0;
	d->digits_max = 0;
	d->count = 0;
	if ((ls->dir = readdir(d->dir_name)))
	{
		d->files = (t_lst *)malloc(sizeof(t_lst));
		d->files->name = ft_strdup(ls->dir->d_name);
		d->files->type = ls->dir->d_type;
		full_info(d->files, d, ls);
		d->files->next = NULL;
		tmp_files = d->files;
	}
	while ((ls->dir = readdir(d->dir_name)))
	{
		d->files->next = (t_lst *)malloc(sizeof(t_lst));
		d->files->next->name = ft_strdup(ls->dir->d_name);
		d->files->next->type = ls->dir->d_type;
		full_info(d->files->next, d, ls);
		d->files->next->next = NULL;
		d->files = d->files->next;
	}
	d->files = tmp_files;
}
