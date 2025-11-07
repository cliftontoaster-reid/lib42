/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:31:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:31:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/vec.h"

Test(vec_set, set_valid_index_updates) {
  t_vec* v = vec_create(sizeof(int));
  int a = 5;
  vec_push_back(v, &a);
  int b = 99;
  bool ok = vec_set(v, 0, &b);
  cr_assert(ok);
  cr_assert_eq(*(int*)vec_get(v, 0), 99);
  vec_free(v);
}

Test(vec_set, set_out_of_bounds_returns_false) {
  t_vec* v = vec_create(sizeof(int));
  int x = 3;
  bool ok = vec_set(v, 5, &x);
  cr_assert_not(ok);
  vec_free(v);
}

Test(vec_set, set_with_null_elem_pointer_behavior) {
  t_vec* v = vec_create(sizeof(int));
  int a = 4;
  vec_push_back(v, &a);
  bool ok = vec_set(v, 0, NULL);
  if (ok) {
    cr_assert_eq(v->size, 1);
  } else {
    cr_assert_eq(v->size, 1);
  }
  vec_free(v);
}

Test(vec_set, set_on_empty_vector_returns_false) {
  t_vec* v = vec_create(sizeof(int));
  int x = 1;
  bool ok = vec_set(v, 0, &x);
  cr_assert_not(ok);
  vec_free(v);
}

Test(vec_set, set_after_resize_preserves_data_when_in_bounds) {
  t_vec* v = vec_create(sizeof(int));
  for (int i = 0; i < 10; ++i) vec_push_back(v, &i);
  size_t old_size = v->size;
  vec_resize(v, 20);
  /* set an in-bounds index */
  int val = 500;
  cr_assert(vec_set(v, 5, &val));
  cr_assert_eq(*(int*)vec_get(v, 5), 500);
  cr_assert_eq(v->size, old_size);
  vec_free(v);
}
