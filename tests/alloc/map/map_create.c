/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:00:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>

#include "42/alloc/map.h"

Test(map_create, create_basic_non_null) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_not_null(m);
  cr_assert_eq(m->size, 0);
  cr_assert_eq(m->default_key_size, 0);
  cr_assert_eq(m->default_value_size, 0);
  map_free(m);
}

Test(map_create, create_with_fixed_sizes) {
  t_map* m = map_create(sizeof(int), sizeof(double), NULL);
  cr_assert_not_null(m);
  cr_assert_eq(m->default_key_size, sizeof(int));
  cr_assert_eq(m->default_value_size, sizeof(double));
  map_free(m);
}

Test(map_create, create_null_cmp_falls_back) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_not_null(m);
  cr_assert_null(m->cmp); /* header permits NULL comparator */
  map_free(m);
}
