/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_foreach_map_find.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:15:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 17:15:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/list.h"
#include "42/alloc/map.h"

static void* collect_keys(const t_map_entry* e, void* arg) {
  (void)arg;
  return e->key;
}

static bool predicate_match_value(const t_map_entry* e, void* arg) {
  int expected = *(int*)arg;
  if (e->value_size != sizeof(int)) return false;
  return *(int*)e->value == expected;
}

Test(map_foreach, foreach_collects_keys_into_list) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, k2 = 2, v1 = 10, v2 = 20;
  cr_assert(map_set(m, &k1, sizeof(k1), &v1, sizeof(v1), 0, NULL, NULL));
  cr_assert(map_set(m, &k2, sizeof(k2), &v2, sizeof(v2), 0, NULL, NULL));
  t_list* keys = map_foreach(m, collect_keys, NULL);
  cr_assert_not_null(keys);
  int count = 0;
  for (t_list* n = keys; n; n = n->next) {
    cr_assert_not_null(n->content);
    count++;
  }
  cr_assert_eq(count, (int)map_size(m));
  /* cleanup allocated result list */
  ft_lstclear(&keys, NULL);
  map_free(m);
}

Test(map_find, find_returns_first_matching_entry) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, k2 = 2, v1 = 100, v2 = 200;
  cr_assert(map_set(m, &k1, sizeof(k1), &v1, sizeof(v1), 0, NULL, NULL));
  cr_assert(map_set(m, &k2, sizeof(k2), &v2, sizeof(v2), 0, NULL, NULL));
  int search_val = 200;
  t_map_entry* e = map_find(m, predicate_match_value, &search_val);
  cr_assert_not_null(e);
  cr_assert_eq(*(int*)e->value, search_val);
  map_free(m);
}

Test(map_foreach, foreach_handles_large_map) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  const int N = 200;
  for (int i = 0; i < N; ++i) {
    int k = i;
    int v = i * 2;
    cr_assert(
        map_set(m, &k, sizeof(k), &v, sizeof(v), MAP_OWN_BOTH, NULL, NULL));
  }
  t_list* keys = map_foreach(m, collect_keys, NULL);
  cr_assert_not_null(keys);
  int count = 0;
  for (t_list* n = keys; n; n = n->next) {
    cr_assert_not_null(n->content);
    /* check that this key exists in the map */
    int found_val = 0;
    size_t found_val_size = 0;
    int key = *(int*)n->content;
    void* val = map_get(m, &key, sizeof(key), &found_val_size);
    cr_assert_not_null(val);
    cr_assert_eq(found_val_size, sizeof(int));
    found_val = *(int*)val;
    cr_assert_eq(found_val, key * 2,
                 "value mismatch for key %d: found %d expected %d", key,
                 found_val, key * 2);
    count++;
  }
  cr_assert_eq(count, (int)map_size(m));
  ft_lstclear(&keys, NULL);
  map_free(m);
}

static bool predicate_none(const t_map_entry* e, void* arg) {
  (void)arg;
  return false;
}

Test(map_find, find_returns_null_when_no_match) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, v1 = 100;
  cr_assert(map_set(m, &k1, sizeof(k1), &v1, sizeof(v1), 0, NULL, NULL));
  t_map_entry* e = map_find(m, predicate_none, NULL);
  cr_assert_null(e);
  map_free(m);
}

static bool predicate_match_even(const t_map_entry* e, void* arg) {
  (void)arg;
  if (e->value_size != sizeof(int)) return false;
  return (*(int*)e->value % 2) == 0;
}

Test(map_find, find_returns_some_matching_entry_among_multiple) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  /* insert several entries, some with even values and some odd */
  for (int i = 1; i <= 20; ++i) {
    int k = i;
    int v = i;
    cr_assert(
        map_set(m, &k, sizeof(k), &v, sizeof(v), MAP_OWN_BOTH, NULL, NULL));
  }
  t_map_entry* e = map_find(m, predicate_match_even, NULL);
  cr_assert_not_null(e);
  cr_assert_eq(*(int*)e->value % 2, 0);
  map_free(m);
}
