/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:30:37 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:30:40 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/vec.h"

Test(vec_pop_back, pop_back_from_non_empty) {
  t_vec* v = vec_create(sizeof(int));
  int x = 9;
  vec_push_back(v, &x);
  cr_assert_eq(v->size, 1);
  bool ok = vec_pop_back(v);
  cr_assert(ok);
  cr_assert_eq(v->size, 0);
  vec_free(v);
}

Test(vec_pop_back, pop_back_on_empty_returns_false) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  bool ok = vec_pop_back(v);
  cr_assert_not(ok);
  vec_free(v);
}

Test(vec_pop_back, pop_back_multiple_until_empty) {
  t_vec* v = vec_create(sizeof(int));
  for (int i = 0; i < 5; ++i) vec_push_back(v, &i);
  for (int i = 0; i < 5; ++i) cr_assert(vec_pop_back(v));
  cr_assert_eq(v->size, 0);
  cr_assert_not(vec_pop_back(v));
  vec_free(v);
}

Test(vec_pop_back, pop_back_updates_size_correctly) {
  t_vec* v = vec_create(sizeof(int));
  int a = 10, b = 20;
  vec_push_back(v, &a);
  vec_push_back(v, &b);
  cr_assert_eq(v->size, 2);
  vec_pop_back(v);
  cr_assert_eq(v->size, 1);
  cr_assert_eq(*(int*)vec_get(v, 0), 10);
  vec_free(v);
}
