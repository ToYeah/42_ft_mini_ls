#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>


typedef struct	s_timelist
{
	char *name;
	struct timespec time;
	struct s_timelist *next;
	struct s_timelist *prev;
}				t_timelist;

t_timelist		*ft_lst_new(char *name,struct timespec time)
{
	t_timelist *lst;

	if (!(lst = malloc(sizeof(t_timelist))))
		return NULL;
	lst->name = name;
	lst->time = time;
	lst->next = NULL;
	lst->prev = NULL;

	return lst;
}



int main()
{
	DIR *dir;
	struct dirent *dp;
	struct stat buf;
	t_timelist *start;
	t_timelist *now;

	now = NULL;

	dir = opendir("./");
	dp = readdir(dir);
	while(dp)
	{
		if (*(dp->d_name) == '.')
		{
			dp = readdir(dir);
			continue;
		}
		stat(dp->d_name,&buf);
		if (now)
		{
			now->next = ft_lst_new(dp->d_name, buf.st_mtimespec);
			(now->next)->prev = now;
			now = now->next;
		}
		else
		{
			now = ft_lst_new(dp->d_name, buf.st_mtimespec);
			now->prev = NULL;
			start = now;
		}
		dp = readdir(dir);
	}
	while(now->prev)
	{
		printf("prev:%s\n",now->name);
		now = now->prev;
	}

	now = start;
	while(now)
	{
		printf("next:%s\n",now->name);
		now = now->next;
	}
}
