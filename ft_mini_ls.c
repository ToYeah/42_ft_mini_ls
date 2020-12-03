#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct	s_timelist
{
	char *name;
	timespec time;
	t_timelist *next;
}				t_timelist;

int main()
{
	DIR *dir;
	struct dirent *dp;
	struct stat buf;

	dir = opendir("./");
	dp = readdir(dir);
	while(dp)
	{
		stat(dp->d_name,&buf);
		printf("%s,%ld\n",dp->d_name,buf.st_mtime.tv_sec);
		dp = readdir(dir);
	}
}
