/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:30:24 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:30:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/vec.h"

Test(vec_create, create_basic_non_null) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  cr_assert_eq(v->size, 0);
  cr_assert(v->capacity == 0);
  cr_assert_eq(v->elem_size, sizeof(int));
  vec_free(v);
}

Test(vec_create, create_elem_size_zero_behavior) {
  t_vec* v = vec_create(0);
  cr_expect_null(v);
  vec_free(v);
}

Test(vec_create, create_multiple_vectors_independent) {
  t_vec* a = vec_create(sizeof(int));
  t_vec* b = vec_create(sizeof(int));
  cr_assert_not_null(a);
  cr_assert_not_null(b);
  int x = 42;
  int y = 7;
  vec_push_back(a, &x);
  vec_push_back(b, &y);
  cr_assert_eq(*(int*)vec_get(a, 0), 42);
  cr_assert_eq(*(int*)vec_get(b, 0), 7);
  vec_free(a);
  vec_free(b);
}

Test(vec_create, create_large_elem_size) {
  size_t large = 1024;
  t_vec* v = vec_create(large);
  cr_assert_not_null(v);
  cr_assert_eq(v->elem_size, large);
  vec_free(v);
}
