/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_cstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:50:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:50:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

Test(map_get_cstr, get_cstr_existing_returns_value) {
  t_map* m = map_create(0, 0, NULL);
  int val = 9;
  cr_assert(map_set_cstr(m, "baz", &val, sizeof(val), 0, NULL));
  size_t out;
  int* v = map_get_cstr(m, "baz", &out);
  cr_assert_not_null(v);
  cr_assert_eq(*v, val);
  cr_assert_eq(out, sizeof(val));
  map_free(m);
}

Test(map_get_cstr, get_cstr_nonexistent_returns_null) {
  t_map* m = map_create(0, 0, NULL);
  size_t out;
  int* v = map_get_cstr(m, "nonexistent", &out);
  cr_assert_null(v);
  map_free(m);
}

Test(map_get_cstr, get_cstr_null_key_returns_null) {
  t_map* m = map_create(0, 0, NULL);
  size_t out;
  int* v = map_get_cstr(m, NULL, &out);
  cr_assert_null(v);
  map_free(m);
}

Test(map_get_cstr, get_cstr_empty_key_returns_value) {
  t_map* m = map_create(0, 0, NULL);
  int val = 42;
  cr_assert(map_set_cstr(m, "", &val, sizeof(val), 0, NULL));
  size_t out;
  int* v = map_get_cstr(m, "", &out);
  cr_assert_not_null(v);
  cr_assert_eq(*v, val);
  cr_assert_eq(out, sizeof(val));
  map_free(m);
}
