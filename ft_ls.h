/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:52:06 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 17:52:12 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>

typedef struct		s_lst
{
	char			*name;
	char			type;
	char			rights[11];
	long			links;
	char			*pw_name;
	char			*gr_name;
	long long		size;
	char			*time;
	time_t			mtime;
	char			*color;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_dir
{
	DIR				*dir_name;
	char			*str_name;
	struct s_lst	*files;
	long			block_size;
	int				digits_max;
	size_t			name_max;
	int				count;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_ls
{
	struct s_dir	*d;
	struct dirent	*dir;

	char			l_flag;
	char			R_flag;
	char			a_flag;
	char			r_flag;
	char			t_flag;

	char			f_flag;
	char			u_flag;
	char			G_flag;
	char			col_flag;
	char			reg_flag;
	char			dir_flag;
	char			link_flag;

}					t_ls;

void	init(t_ls *ls);

int		bonus_flag(char *str, t_ls *ls);
int		set_flags(char *str, int i, t_ls *ls);
void	new_flag(char *str, t_ls *ls);

t_dir	*set_dir(t_ls *ls, char *str);
void	new_dir(char *str, t_ls *ls);
void	recursive(t_lst *files, t_ls *ls, char *dname);

void	get_files(t_dir *d, t_ls *ls);
void	full_info(t_lst *file, t_dir *d, t_ls *ls);
char	*full_name(char *dname, char *fname);

void	write_to_list(t_ls *ls);

int		asc(t_lst *l1, t_lst *l2);
int		desc(t_lst *l1, t_lst *l2);
int		desc_time(t_lst *l1, t_lst *l2);

void	swap1(t_lst *l1, t_lst *l2);
void	swap2(t_lst *l1, t_lst *l2);
void	sort_list(t_lst	*list, int (*cmp)(t_lst*, t_lst*));

void	print(t_ls *ls);

#endif
