/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:10:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:10:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

static int freed_key_count;
static int freed_value_count;

static void counting_free_key(void* p) {
  (void)p;
  freed_key_count++;
}
static void counting_free_value(void* p) {
  (void)p;
  freed_value_count++;
}

Test(map_set, set_null_map_returns_false) {
  errno = 0;
  int key = 1;
  int val = 2;
  cr_assert_not(
      map_set(NULL, &key, sizeof(key), &val, sizeof(val), 0, NULL, NULL));
  cr_assert_eq(errno, EINVAL);
}

Test(map_set, set_null_key_returns_false) {
  t_map* m = map_create(0, 0, NULL);
  errno = 0;
  int val = 2;
  cr_assert_not(map_set(m, NULL, 1, &val, sizeof(val), 0, NULL, NULL));
  cr_assert_eq(errno, EINVAL);
  map_free(m);
}

Test(map_set, set_zero_key_size_returns_false) {
  t_map* m = map_create(0, 0, NULL);
  errno = 0;
  int key = 1;
  int val = 2;
  cr_assert_not(map_set(m, &key, 0, &val, sizeof(val), 0, NULL, NULL));
  cr_assert_eq(errno, EINVAL);
  map_free(m);
}

Test(map_set, set_basic_insert_unowned) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k = 42;
  int v = 100;
  cr_assert(map_set(m, &k, sizeof(k), &v, sizeof(v), 0, NULL, NULL));
  size_t out_size;
  int* rv = map_get(m, &k, sizeof(k), &out_size);
  cr_assert_not_null(rv);
  cr_assert_eq(*rv, v);
  cr_assert_eq(out_size, sizeof(v));
  cr_assert_eq(map_size(m), 1);
  map_free(m);
}

Test(map_set, set_owned_both_and_free_on_map_free) {
  t_map* m = map_create(0, 0, NULL);
  freed_key_count = 0;
  freed_value_count = 0;
  char* k = strdup("k1");
  char* v = strdup("val1");
  cr_assert(map_set(m, k, strlen(k) + 1, v, strlen(v) + 1, MAP_OWN_BOTH,
                    counting_free_key, counting_free_value));
  cr_assert_eq(map_size(m), 1);
  map_free(m);
  cr_assert_eq(freed_key_count, 1);
  cr_assert_eq(freed_value_count, 1);
}

Test(map_set, set_update_existing_key_replaces_value) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k = 7;
  int v1 = 1;
  int v2 = 2;
  cr_assert(map_set(m, &k, sizeof(k), &v1, sizeof(v1), 0, NULL, NULL));
  cr_assert_eq(map_size(m), 1);
  cr_assert(map_set(m, &k, sizeof(k), &v2, sizeof(v2), 0, NULL, NULL));
  cr_assert_eq(map_size(m), 1);
  size_t out_size;
  int* rv = map_get(m, &k, sizeof(k), &out_size);
  cr_assert_not_null(rv);
  cr_assert_eq(*rv, v2);
  map_free(m);
}
