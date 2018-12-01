#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"
#include <errno.h>
// #include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
// #include <unistd.h>
#include <pwd.h>
#include <grp.h>

typedef struct		s_lst
{
	char			*name;
	char			type;
	char			rights[10]; // type and rights of file
	long			links;
	char			*pw_name;
	char			*gr_name;
	long long		size;
	char			*time;
	time_t			mtime;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_dir
{
	DIR				*dir_name;
	char			*str_name;
	struct s_lst	*files; //list of files and directories which we should print
	long			block_size;
	int			digits_max;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_ls
{
	struct s_dir	*d;    //list of directories
	struct dirent	*dir;

	char			l_flag;
	char			R_flag;
	char			a_flag;
	char			r_flag;
	char			t_flag;

}					t_ls;

void	init(t_ls *ls);

void	new_dir(char *str, t_ls *ls);
void	new_flag(char *str, t_ls *ls);
void	write_to_list(t_ls *ls);

long	get_files(t_dir *d, t_ls *ls);
void	full_info(t_lst *file, char *dname, long *total, t_ls *ls, int *max);

int		asc(t_lst *l1, t_lst *l2);
int		desc(t_lst *l1, t_lst *l2);
int		desc_time(t_lst *l1, t_lst *l2);
void	sort_list(t_lst	*list, int (*cmp)(t_lst*, t_lst*));

void	print(t_ls *ls);

#endif
