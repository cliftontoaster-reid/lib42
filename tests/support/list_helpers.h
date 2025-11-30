/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:00:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:00:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

#include "42/alloc/list.h"

/* Helpers for tests */
int* make_int_content(int value);
char* make_dup_string(const char* s);
t_list* make_int_node(int value);
t_list* make_string_node(const char* s);
void free_int_content(void* p);
void free_string_content(void* p);

/* Spy functions to record calls */
void spy_del_free(void* p);
void spy_and_free_del(void* p);
size_t spy_del_count(void);
void spy_del_reset(void);

/* Iterator spy */
void spy_iter_record(void* p);
size_t spy_iter_count(void);
void spy_iter_reset(void);

/* Assertions */
int assert_list_ints(t_list* lst, int expected[], size_t size);
