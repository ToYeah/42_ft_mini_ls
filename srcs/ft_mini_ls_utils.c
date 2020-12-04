/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei </var/mail/totaisei>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:46:13 by totaisei          #+#    #+#             */
/*   Updated: 2020/12/04 21:50:16 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls_utils.h"

char*ft_strdup(const char *s1)
{
	char*result;
	inti;

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

t_timelist*ft_lst_new(char *name,struct timespec time)
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
	free(min->name);
	free(min);
	return res;
}
