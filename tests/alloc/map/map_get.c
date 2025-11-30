/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:25:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:25:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

Test(map_get, get_null_map_returns_null) {
  int k = 1;
  size_t out;
  errno = 0;
  void* v = map_get(NULL, &k, sizeof(k), &out);
  cr_assert_null(v);
  cr_assert(errno == EINVAL || errno == 0);
}

Test(map_get, get_nonexistent_returns_null_and_no_errno) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k = 2;
  size_t out;
  errno = 0;
  void* v = map_get(m, &k, sizeof(k), &out);
  cr_assert_null(v);
  cr_assert_eq(errno, 0);
  map_free(m);
}

Test(map_get, get_existing_returns_value_and_size) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k = 3;
  int val = 84;
  cr_assert(map_set(m, &k, sizeof(k), &val, sizeof(val), 0, NULL, NULL));
  size_t out_size = 0;
  int* v = map_get(m, &k, sizeof(k), &out_size);
  cr_assert_not_null(v);
  cr_assert_eq(*v, val);
  cr_assert_eq(out_size, sizeof(val));
  map_free(m);
}
