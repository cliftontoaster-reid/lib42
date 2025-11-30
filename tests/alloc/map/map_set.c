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
static void counting_free_value_and_free(void* p) {
  if (p) free(p);
  freed_value_count++;
}
static void counting_free_key_and_free(void* p) {
  if (p) free(p);
  freed_key_count++;
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

Test(map_set, owned_value_freed_on_update_and_free) {
  t_map* m = map_create(0, 0, NULL);
  freed_value_count = 0;
  char* v1 = strdup("v1");
  char* v2 = strdup("v2");
  cr_assert(map_set(m, "k", strlen("k") + 1, v1, strlen(v1) + 1, MAP_OWN_VALUE,
                    NULL, counting_free_value_and_free));
  /* Update: replace with another owned value; should free v1 */
  cr_assert(map_set(m, "k", strlen("k") + 1, v2, strlen(v2) + 1, MAP_OWN_VALUE,
                    NULL, counting_free_value_and_free));
  /* v1 freed during update */
  cr_assert_eq(freed_value_count, 1);
  map_free(m);
  /* v2 freed during map_free */
  cr_assert_eq(freed_value_count, 2);
}

Test(map_set, change_unowned_value_to_owned_does_not_free_old_value) {
  t_map* m = map_create(0, 0, NULL);
  freed_value_count = 0;
  char* v1 = strdup("v1");
  char* v2 = strdup("v2");
  /* Insert unowned value (map should not free v1) */
  cr_assert(
      map_set(m, "k2", strlen("k2") + 1, v1, strlen(v1) + 1, 0, NULL, NULL));
  /* Update to owned value; should NOT free v1 since it was unowned */
  cr_assert(map_set(m, "k2", strlen("k2") + 1, v2, strlen(v2) + 1,
                    MAP_OWN_VALUE, NULL, counting_free_value_and_free));
  cr_assert_eq(freed_value_count, 0);
  /* map_free should free v2 only (owned) */
  map_free(m);
  cr_assert_eq(freed_value_count, 1);
  /* We must free v1 manually since it was unowned */
  free(v1);
}

Test(map_set, owned_key_persists_after_update_and_freed_on_map_free) {
  t_map* m = map_create(0, 0, NULL);
  freed_key_count = 0;
  freed_value_count = 0;
  char* k1 = strdup("keyp");
  char* k2 = strdup("keyp");
  char* v1 = strdup("val1");
  char* v2 = strdup("val2");
  /* initial insert: own key, unowned value */
  cr_assert(map_set(m, k1, strlen(k1) + 1, v1, strlen(v1) + 1, MAP_OWN_KEY,
                    counting_free_key_and_free, NULL));
  /* update: pass a different pointer with same key content; new value owned */
  cr_assert(map_set(m, k2, strlen(k2) + 1, v2, strlen(v2) + 1, MAP_OWN_VALUE,
                    NULL, counting_free_value_and_free));
  /* key should be freed by map_free only once */
  map_free(m);
  cr_assert_eq(freed_key_count, 1);
  cr_assert_eq(freed_value_count, 1);
}
