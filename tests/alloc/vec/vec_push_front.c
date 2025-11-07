/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:31:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:31:01 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/vec.h"

Test(vec_push_front, push_front_single_element) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  int x = 11;
  cr_assert(vec_push_front(v, &x));
  cr_assert_eq(v->size, 1);
  cr_assert_eq(*(int*)vec_get(v, 0), 11);
  vec_free(v);
}

Test(vec_push_front, push_front_multiple_order_preserved) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  int a = 1, b = 2, c = 3;
  cr_assert(vec_push_front(v, &a));
  cr_assert(vec_push_front(v, &b));
  cr_assert(vec_push_front(v, &c));
  /* order should be c, b, a */
  cr_assert_eq(*(int*)vec_get(v, 0), 3);
  cr_assert_eq(*(int*)vec_get(v, 1), 2);
  cr_assert_eq(*(int*)vec_get(v, 2), 1);
  vec_free(v);
}

Test(vec_push_front, push_front_resize_when_full) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  for (int i = 0; i < 100; ++i) {
    cr_assert(vec_push_front(v, &i));
  }
  cr_assert_eq((int)v->size, 100);
  vec_free(v);
}

Test(vec_push_front, push_front_after_pop_front) {
  t_vec* v = vec_create(sizeof(int));
  int a = 5, b = 6;
  cr_assert(vec_push_front(v, &a));
  cr_assert(vec_push_front(v, &b));
  cr_assert(vec_pop_front(v));
  int c = 77;
  cr_assert(vec_push_front(v, &c));
  cr_assert_eq(*(int*)vec_get(v, 0), 77);
  vec_free(v);
}

Test(vec_push_front, push_front_null_elem_pointer_behavior) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  bool ok = vec_push_front(v, NULL);
  if (ok)
    cr_assert_eq(v->size, 1);
  else
    cr_assert_eq(v->size, 0);
  vec_free(v);
}
