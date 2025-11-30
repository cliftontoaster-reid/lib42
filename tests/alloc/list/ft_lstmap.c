/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:15:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 20:15:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>

#include "support/list_helpers.h"

void* int_to_string(void* p) {
  if (!p) return NULL;
  int v = *(int*)p;
  char* s = malloc(16);
  if (!s) return NULL;
  snprintf(s, 16, "%d", v);
  return s;
}

void* int_to_string_null_on_2(void* p) {
  if (!p) return NULL;
  int v = *(int*)p;
  if (v == 2) return NULL; /* simulate failure for the second element */
  char* s = malloc(16);
  if (!s) return NULL;
  snprintf(s, 16, "%d", v);
  return s;
}

Test(ft_lstmap, null_list_returns_null) {
  cr_assert_null(ft_lstmap(NULL, int_to_string, free_string_content));
}

Test(ft_lstmap, null_f_returns_null) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  cr_assert_null(ft_lstmap(list, NULL, free_string_content));
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstmap, maps_ints_to_strings_and_preserves_order) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  t_list* mapped = ft_lstmap(list, int_to_string, free_string_content);
  cr_assert_not_null(mapped);
  /* verify values */
  t_list* cur = mapped;
  cr_assert_str_eq((char*)cur->content, "1");
  cur = cur->next;
  cr_assert_str_eq((char*)cur->content, "2");
  cur = cur->next;
  cr_assert_str_eq((char*)cur->content, "3");
  ft_lstclear(&mapped, free_string_content);
  ft_lstclear(&list, free_int_content);
}

Test(ft_lstmap, f_returns_null_frees_allocated_and_returns_null) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  spy_del_reset();
  t_list* mapped = ft_lstmap(list, int_to_string_null_on_2, spy_and_free_del);
  cr_assert_null(mapped);
  /* one transform created and then freed for value 1 */
  cr_assert_eq(spy_del_count(), 1);
  ft_lstclear(&list, free_int_content);
}
