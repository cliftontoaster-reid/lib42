/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:30:31 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:30:34 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/vec.h"

Test(vec_get, get_valid_index_returns_pointer) {
  t_vec* v = vec_create(sizeof(int));
  int x = 77;
  vec_push_back(v, &x);
  int* p = vec_get(v, 0);
  cr_assert_not_null(p);
  cr_assert_eq(*p, 77);
  vec_free(v);
}

Test(vec_get, get_out_of_bounds_returns_null) {
  t_vec* v = vec_create(sizeof(int));
  vec_push_back(v, &(int){1});
  void* p = vec_get(v, 5);
  cr_assert_null(p);
  vec_free(v);
}

Test(vec_get, get_after_push_and_pop_consistency) {
  t_vec* v = vec_create(sizeof(int));
  int a = 1, b = 2, c = 3;
  vec_push_back(v, &a);
  vec_push_back(v, &b);
  vec_push_back(v, &c);
  vec_pop_front(v); /* now b,c */
  int* p0 = vec_get(v, 0);
  int* p1 = vec_get(v, 1);
  cr_assert_not_null(p0);
  cr_assert_not_null(p1);
  cr_assert_eq(*p0, 2);
  cr_assert_eq(*p1, 3);
  vec_free(v);
}

Test(vec_get, get_on_null_vector_returns_null) {
  void* p = vec_get(NULL, 0);
  cr_assert_null(p);
}

Test(vec_get, get_mutable_modify_reflects_in_vector) {
  t_vec* v = vec_create(sizeof(int));
  int x = 9;
  vec_push_back(v, &x);
  int* p = vec_get(v, 0);
  cr_assert_not_null(p);
  *p = 1234;
  int* q = vec_get(v, 0);
  cr_assert_eq(*q, 1234);
  vec_free(v);
}
