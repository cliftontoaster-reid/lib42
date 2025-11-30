/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:30:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 17:30:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/map.h"

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

static void inc_value(t_map_entry* e, void* arg) {
  (void)arg;
  if (e->value_size == sizeof(int)) {
    int* v = (int*)e->value;
    *v = *v + 1;
  }
}

Test(map_map, map_mutates_values_inside_entries) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, v1 = 0;
  int k2 = 2, v2 = 10;
  cr_assert(map_set(m, &k1, sizeof(k1), &v1, sizeof(v1), 0, NULL, NULL));
  cr_assert(map_set(m, &k2, sizeof(k2), &v2, sizeof(v2), 0, NULL, NULL));
  map_map(m, inc_value, NULL);
  size_t out;
  cr_assert_eq(*(int*)map_get(m, &k1, sizeof(k1), &out), 1);
  cr_assert_eq(*(int*)map_get(m, &k2, sizeof(k2), &out), 11);
  map_free(m);
}
