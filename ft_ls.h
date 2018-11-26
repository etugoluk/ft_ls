#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"
// #include <sys/types.h>
#include <dirent.h>
// #include <sys/stat.h>
// #include <unistd.h>

typedef struct	s_ls
{
	DIR			*d;
	struct dirent *dir;
}				t_ls;

#endif
