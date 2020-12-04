/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei </var/mail/totaisei>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:47:48 by totaisei          #+#    #+#             */
/*   Updated: 2020/12/04 21:51:08 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

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

#endif
