/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:58:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:58:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/map.h"

Test(map_size, size_null_map) { cr_assert_eq(map_size(NULL), 0); }

Test(map_size, size_after_inserts_and_removes) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, k2 = 2;
  int v = 0;
  cr_assert_eq(map_size(m), 0);
  cr_assert(map_set(m, &k1, sizeof(k1), &v, sizeof(v), 0, NULL, NULL));
  cr_assert_eq(map_size(m), 1);
  cr_assert(map_set(m, &k2, sizeof(k2), &v, sizeof(v), 0, NULL, NULL));
  cr_assert_eq(map_size(m), 2);
  cr_assert(map_remove(m, &k1, sizeof(k1)));
  cr_assert_eq(map_size(m), 1);
  map_free(m);
}
