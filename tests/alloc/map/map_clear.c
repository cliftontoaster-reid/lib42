/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:12:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 18:12:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

Test(map_clear, clear_empty_map_noop) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  cr_assert_eq(map_size(m), 0);
  map_clear(m);
  cr_assert_eq(map_size(m), 0);
  map_free(m);
}

Test(map_clear, clear_multiple_removes_entries) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, k2 = 2, v = 0;
  cr_assert(map_set(m, &k1, sizeof(k1), &v, sizeof(v), 0, NULL, NULL));
  cr_assert(map_set(m, &k2, sizeof(k2), &v, sizeof(v), 0, NULL, NULL));
  cr_assert_eq(map_size(m), 2);
  map_clear(m);
  cr_assert_eq(map_size(m), 0);
  map_free(m);
}
