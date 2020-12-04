#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct	s_timelist
{
	char *name;
	struct timespec time;
	struct s_timelist *next;
	struct s_timelist *prev;
}				t_timelist;

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

char*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	i++;
	result = (char *)malloc(sizeof(char) * i);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

t_timelist		*ft_lst_new(char *name,struct timespec time)
{
	t_timelist *lst;

	if (!(lst = malloc(sizeof(t_timelist))))
		return NULL;
	if (!(lst->name = ft_strdup(name)))
		return NULL;
	lst->time = time;
	lst->next = NULL;
	lst->prev = NULL;

	return lst;
}

int compare_lst(t_timelist *min, t_timelist *now)
{
	if (now == min)
		return FALSE;
	if (now->time.tv_sec < min->time.tv_sec)
		return TRUE;
	else if (now->time.tv_sec == min->time.tv_sec)
	{
		if(now->time.tv_nsec < min->time.tv_nsec)
			return TRUE;
		else if (now->time.tv_nsec == min->time.tv_nsec)
		{
			if (ft_strcmp(min->name,now->name) < 0)
				return TRUE;
		}
	}
	return FALSE;
}


t_timelist *get_minlst(t_timelist *start)
{
	t_timelist *min;
	t_timelist *now;

	if (!start)
		return NULL;
	now = start;
	min = start;
	while(now)
	{
		if(compare_lst(min, now))
			min = now;
		now = now->next;
	}
	return min;
}

t_timelist *del_min_lst(t_timelist *start,t_timelist *min)
{
	t_timelist *res;

	res = start;
	if(min->next)
		(min->next)->prev = min->prev;
	if(min->prev)
		(min->prev)->next = min->next;
	if(min == start)
		res = min->next;
	free(min);
	return res;
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
