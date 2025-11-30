/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:05:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:05:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "support/list_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implementation of helpers */
int* make_int_content(int value) {
  int* p = malloc(sizeof(int));
  if (!p) return NULL;
  *p = value;
  return p;
}

char* make_dup_string(const char* s) {
  if (!s) return NULL;
  char* dup = strdup(s);
  return dup;
}

t_list* make_int_node(int value) {
  int* p = make_int_content(value);
  if (!p) return NULL;
  t_list* node = ft_lstnew(p);
  if (!node) {
    free(p);
    return NULL;
  }
  return node;
}

t_list* make_string_node(const char* s) {
  char* copy = make_dup_string(s);
  if (!copy && s) return NULL;
  t_list* node = ft_lstnew(copy);
  if (!node) {
    free(copy);
    return NULL;
  }
  return node;
}

void free_int_content(void* p) { free(p); }
void free_string_content(void* p) { free(p); }

/* Spy implementation */
static size_t s_spy_del_count = 0;
void spy_del_free(void* p) {
  (void)p;
  s_spy_del_count++;
}
void spy_and_free_del(void* p) {
  if (p) free(p);
  s_spy_del_count++;
}
size_t spy_del_count(void) { return s_spy_del_count; }
void spy_del_reset(void) { s_spy_del_count = 0; }

static size_t s_spy_iter_count = 0;
void spy_iter_record(void* p) {
  (void)p;
  s_spy_iter_count++;
}
size_t spy_iter_count(void) { return s_spy_iter_count; }
void spy_iter_reset(void) { s_spy_iter_count = 0; }

/* Assertions */
int assert_list_ints(t_list* lst, int expected[], size_t size) {
  size_t i = 0;
  t_list* cur = lst;
  while (cur && i < size) {
    if (!cur->content) return 0;
    if (*(int*)cur->content != expected[i]) return 0;
    cur = cur->next;
    i++;
  }
  return (i == size && cur == NULL);
}
