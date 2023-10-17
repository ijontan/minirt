/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:34:20 by itan              #+#    #+#             */
/*   Updated: 2023/10/02 18:28:36 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROFILER_H
# define PROFILER_H
#include "libft.h"
#include <time.h>
#include <stdio.h>

extern t_ht	*ht_value;
extern t_ht	*ht_count;

#define profile(key, exp) \
({ \
	long long int diff; \
	long long int *value; \
	long long int *count; \
	if (!ht_value) \
		ht_value = ft_ht_create(); \
	if (!ht_count) \
		ht_count = ft_ht_create(); \
\
	struct timespec res1,res2; \
	clock_gettime(CLOCK_REALTIME, &res1); \
	exp; \
	clock_gettime(CLOCK_REALTIME, &res2); \
\
	diff = (res2.tv_sec - res1.tv_sec) * 1000000000 + (res2.tv_nsec - res1.tv_nsec); \
\
	value = (long long int *)ft_ht_get(*ht_value, key); \
	if (!value) \
	{ \
		value = (long long int *)ft_calloc(1, sizeof(long long int)); \
		ft_ht_set(ht_value, key, value); \
	} \
	*value += diff; \
\
	count = (long long int *)ft_ht_get(*ht_count, key); \
	if (!count) \
	{ \
		count = (long long int *)ft_calloc(1, sizeof(long long int)); \
		ft_ht_set(ht_count, key, count); \
	} \
	++(*count); \
})

#define print_profile() \
({ \
	if (ht_value && ht_count)\
	{\
		t_entry	*entries;\
		t_entry	*entry;\
		for (int i = 0;i < TABLE_SIZE; ++i)\
		{\
			entries = ht_value->entries[i];\
			entry = entries;\
			while (entry)\
			{\
				char *key = entry->key;\
				float total = *(long long *)entry->value;\
				float count = *(long long *)ft_ht_get(*ht_count, key);\
				float avg = total / count;\
				printf("%s -> total: %.6e, count: %.6e, avg: %.6e.\n", key, total, count, avg);\
				entry = entry->next;\
			}\
		}\
	}\
})

#endif

