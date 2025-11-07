/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:30:48 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:30:52 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/vec.h"

Test(vec_push_back, push_back_single_element) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  int x = 123;
  bool ok = vec_push_back(v, &x);
  cr_assert(ok);
  cr_assert_eq(v->size, 1);
  int* p = vec_get(v, 0);
  cr_assert_not_null(p);
  cr_assert_eq(*p, 123);
  vec_free(v);
}

Test(vec_push_back, push_back_multiple_resize) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  const int N = 200;
  for (int i = 0; i < N; ++i) {
    cr_assert(vec_push_back(v, &i));
  }
  cr_assert_eq((int)v->size, N);
  for (int i = 0; i < N; ++i) {
    int* p = vec_get(v, i);
    cr_assert_not_null(p);
    cr_assert_eq(*p, i);
  }
  vec_free(v);
}

Test(vec_push_back, push_back_various_elem_sizes) {
  struct two {
    int a;
    char b;
  } s = {.a = 5, .b = 'Z'};
  t_vec* v = vec_create(sizeof(s));
  cr_assert_not_null(v);
  cr_assert(vec_push_back(v, &s));
  struct two* p = vec_get(v, 0);
  cr_assert_not_null(p);
  cr_assert_eq(p->a, 5);
  cr_assert_eq(p->b, 'Z');
  vec_free(v);
}

Test(vec_push_back, push_back_after_pop_back) {
  t_vec* v = vec_create(sizeof(int));
  int a = 1, b = 2;
  cr_assert(vec_push_back(v, &a));
  cr_assert(vec_push_back(v, &b));
  cr_assert(vec_pop_back(v));
  cr_assert_eq(v->size, 1);
  int c = 99;
  bool ok = vec_push_back(v, &c);
  if (ok) cr_assert_eq(*(int*)vec_get(v, v->size - 1), 99);
  vec_free(v);
}

Test(vec_push_back, push_back_null_elem_pointer_behavior) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  bool ok = vec_push_back(v, NULL);
  /* implementation-defined: either return false and not change size, or accept
   */
  if (ok)
    cr_assert_eq(v->size, 1);
  else
    cr_assert_eq(v->size, 0);
  vec_free(v);
}
