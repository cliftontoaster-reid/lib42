/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set_cstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:45:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:45:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

Test(map_set_cstr, set_cstr_null_map_returns_error) {
  errno = 0;
  int val = 1;
  cr_assert_not(map_set_cstr(NULL, "k", &val, sizeof(val), 0, NULL));
  cr_assert_eq(errno, EINVAL);
}

Test(map_set_cstr, set_cstr_basic_inserts_key_copy) {
  t_map* m = map_create(0, 0, NULL);
  int val = 5;
  cr_assert(map_set_cstr(m, "hello", &val, sizeof(val), 0, NULL));
  size_t out_size;
  int* v = map_get_cstr(m, "hello", &out_size);
  cr_assert_not_null(v);
  cr_assert_eq(*v, val);
  cr_assert_eq(out_size, sizeof(val));
  map_free(m);
}
