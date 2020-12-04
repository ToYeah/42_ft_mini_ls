#include "ft_mini_ls.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;

	i = 0;
	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	while (1)
	{
		if ((casted_s1[i] - casted_s2[i]) != 0)
			return (casted_s1[i] - casted_s2[i]);
		if(!casted_s1[i] && !casted_s2[i])
			break;
		i++;
	}
	return (0);
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
		lstat(dp->d_name,&buf);
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
	now = start;
	while(start)
	{
		now = get_minlst(start);
		if (now)
			printf("%s\n",now->name);
		start = del_min_lst(start, now);
	}

	now = start;
}
