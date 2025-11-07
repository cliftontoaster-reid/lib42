/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:40:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "alloc/list.h"

static void* dup_upper(void* s) {
  if (!s) return NULL;
  char* in = s;
  char* out = strdup(in);
  if (!out) return NULL;
  for (size_t i = 0; out[i]; ++i) out[i] = toupper((unsigned char)out[i]);
  return out;
}

static void* dup_maybe_fail(void* s) {
  if (!s) return NULL;
  if (strcmp((char*)s, "BAD") == 0)
    return NULL; /* simulate allocation failure for this element */
  return strdup((char*)s);
}

static int freed_count;
static void counting_del(void* p) {
  if (p) freed_count++;
  free(p);
}

Test(ft_lstmap, maps_and_allocates_new_list) {
  t_list* src = ft_lstnew("one");
  ft_lstadd_back(&src, ft_lstnew("Two"));
  ft_lstadd_back(&src, ft_lstnew("three"));

  t_list* dst = ft_lstmap(src, dup_upper, counting_del);
  cr_assert_not_null(dst);

  cr_assert_str_eq((char*)dst->content, "ONE");
  cr_assert_str_eq((char*)dst->next->content, "TWO");
  cr_assert_str_eq((char*)dst->next->next->content, "THREE");

  /* original unchanged */
  cr_assert_str_eq((char*)src->content, "one");

  ft_lstclear(&dst, counting_del);
  /* dst cleared => counting_del called 3 times */
  cr_assert_eq(freed_count, 3);

  /* cleanup source (no allocated content) */
  ft_lstclear(&src, NULL);
}

Test(ft_lstmap, returns_null_on_failure_and_cleans_partial_allocs) {
  t_list* src = ft_lstnew("ok1");
  ft_lstadd_back(&src, ft_lstnew("BAD"));
  ft_lstadd_back(&src, ft_lstnew("ok2"));

  freed_count = 0;
  t_list* dst = ft_lstmap(src, dup_maybe_fail, counting_del);
  cr_assert_null(dst);
  cr_assert_eq(freed_count, 1);

  ft_lstclear(&src, NULL);
}

Test(ft_lstmap, null_source_returns_null) {
  t_list* dst = ft_lstmap(NULL, dup_upper, counting_del);
  cr_assert_null(dst);
}
