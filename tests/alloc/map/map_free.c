/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:05:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:05:00 by lfiorell          ###   ########.fr */
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

Test(map_free, free_null_map) { map_free(NULL); }

Test(map_free, free_empty_map) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_not_null(m);
  map_free(m);
}

Test(map_free, free_owned_resources_calls_destructors) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_not_null(m);
  freed_keys = 0;
  freed_values = 0;
  char* k = strdup("key");
  char* v = strdup("val");
  cr_assert(map_set(m, k, strlen(k) + 1, v, strlen(v) + 1, MAP_OWN_BOTH,
                    counting_free_key, counting_free_value));
  map_free(m);
  /* both custom destructors called exactly once */
  cr_assert_eq(freed_keys, 1);
  cr_assert_eq(freed_values, 1);
}
