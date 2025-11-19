/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:30:45 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:30:45 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/vec.h"

Test(vec_pop_front, pop_front_from_non_empty) {
  t_vec* v = vec_create(sizeof(int));
  int a = 1;
  vec_push_back(v, &a);
  cr_assert_eq(v->size, 1);
  bool ok = vec_pop_front(v);
  cr_assert(ok);
  cr_assert_eq(v->size, 0);
  vec_free(v);
}

Test(vec_pop_front, pop_front_on_empty_returns_false) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  bool ok = vec_pop_front(v);
  cr_assert_not(ok);
  vec_free(v);
}

Test(vec_pop_front, pop_front_order_preserved_after_multiple) {
  t_vec* v = vec_create(sizeof(int));
  int a = 1, b = 2, c = 3;
  vec_push_back(v, &a);
  vec_push_back(v, &b);
  vec_push_back(v, &c);
  cr_assert(vec_pop_front(v)); /* removes a */
  cr_assert_eq(*(int*)vec_get(v, 0), 2);
  cr_assert(vec_pop_front(v));
  cr_assert_eq(*(int*)vec_get(v, 0), 3);
  vec_free(v);
}

Test(vec_pop_front, pop_front_updates_size_correctly) {
  t_vec* v = vec_create(sizeof(int));
  int a = 5, b = 6;
  vec_push_back(v, &a);
  vec_push_back(v, &b);
  cr_assert_eq(v->size, 2);
  vec_pop_front(v);
  cr_assert_eq(v->size, 1);
  vec_free(v);
}
