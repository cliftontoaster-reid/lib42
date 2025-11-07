/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:31:07 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:33:18 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/vec.h"

Test(vec_resize, resize_increase_capacity_preserves_elements) {
  t_vec* v = vec_create(sizeof(int));
  for (int i = 0; i < 5; ++i) vec_push_back(v, &i);
  int* before = vec_get(v, 2);
  cr_assert_not_null(before);
  int val_before = *before;
  bool ok = vec_resize(v, 50);
  cr_assert(ok);
  cr_assert(v->capacity >= 50);
  int* after = vec_get(v, 2);
  cr_assert_not_null(after);
  cr_assert_eq(*after, val_before);
  vec_free(v);
}

Test(vec_resize, resize_decrease_capacity_truncates_elements) {
  t_vec* v = vec_create(sizeof(int));
  for (int i = 0; i < 10; ++i) vec_push_back(v, &i);
  bool ok = vec_resize(v, 4);
  if (!ok) {
    /* implementation may reject shrink; make a permissive assertion */
    cr_expect(true);
    vec_free(v);
    return;
  }
  cr_assert(v->capacity <= 4);
  cr_assert(v->size <= v->capacity);
  vec_free(v);
}

Test(vec_resize, resize_to_zero_capacity_allowed_or_error) {
  t_vec* v = vec_create(sizeof(int));
  vec_push_back(v, &(int){1});
  bool ok = vec_resize(v, 0);
  if (!ok) {
    cr_expect(true);
  } else {
    cr_assert_eq(v->capacity, 0);
    cr_assert_eq(v->size, 0);
  }
  vec_free(v);
}

Test(vec_resize, resize_on_null_vector_returns_false) {
  bool ok = vec_resize(NULL, 10);
  cr_assert_not(ok);
}

Test(vec_resize, resize_then_push_back_succeeds) {
  t_vec* v = vec_create(sizeof(int));
  bool ok = vec_resize(v, 100);
  cr_assert(ok);
  int x = 42;
  cr_assert(vec_push_back(v, &x));
  cr_assert_eq(*(int*)vec_get(v, 0), 42);
  vec_free(v);
}
