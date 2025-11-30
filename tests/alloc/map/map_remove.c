/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:35:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:35:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

static int freed_keys;
static int freed_values;
static void counting_free_key(void* p) {
  (void)p;
  freed_keys++;
}
static void counting_free_value(void* p) {
  (void)p;
  freed_values++;
}

Test(map_remove, remove_null_map_returns_error) {
  int k = 1;
  errno = 0;
  cr_assert_not(map_remove(NULL, &k, sizeof(k)));
  cr_assert_eq(errno, EINVAL);
}

Test(map_remove, remove_nonexistent_returns_ENOENT) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k = 10;
  errno = 0;
  cr_assert_not(map_remove(m, &k, sizeof(k)));
  cr_assert_eq(errno, ENOENT);
  map_free(m);
}

Test(map_remove, remove_existing_decrements_size_and_frees_owned) {
  t_map* m = map_create(0, 0, NULL);
  freed_keys = 0;
  freed_values = 0;
  char* k = strdup("k_rm");
  char* v = strdup("v_rm");
  cr_assert(map_set(m, k, strlen(k) + 1, v, strlen(v) + 1, MAP_OWN_BOTH,
                    counting_free_key, counting_free_value));
  cr_assert_eq(map_size(m), 1);
  cr_assert(map_remove(m, k, strlen(k) + 1));
  cr_assert_eq(map_size(m), 0);
  cr_assert_eq(freed_keys, 1);
  cr_assert_eq(freed_values, 1);
  map_free(m);
}
