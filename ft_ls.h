#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"
#include <errno.h>
// #include <sys/types.h>
#include <dirent.h>
// #include <sys/stat.h>
// #include <unistd.h>

typedef struct		s_lst
{
	char			*name;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_dir
{
	DIR				*dir_name;
	char			*str_name;
	struct s_lst	*files; //list of files and directories which we should print
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

int		asc(char *a, char *b);
int		desc(char *a, char *b);
void	sort_list(t_lst	*list, int (*cmp)(char*, char*));

void	print(t_ls *ls);

#endif
