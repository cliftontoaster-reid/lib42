/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_remove_cstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:52:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 16:52:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"

Test(map_remove_cstr, remove_cstr_existing_removes_and_frees_owned) {
  t_map* m = map_create(0, 0, NULL);
  int val = 42;
  cr_assert(map_set_cstr(m, "rm_me", &val, sizeof(val), 0, NULL));
  cr_assert(map_remove_cstr(m, "rm_me"));
  size_t out;
  cr_assert_null(map_get_cstr(m, "rm_me", &out));
  map_free(m);
}

Test(map_remove_cstr, remove_cstr_nonexistent_returns_false) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_not(map_remove_cstr(m, "nonexistent"));
  map_free(m);
}

Test(map_remove_cstr, remove_cstr_null_key_returns_false) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_not(map_remove_cstr(m, NULL));
  map_free(m);
}

Test(map_remove_cstr, remove_cstr_empty_key) {
  t_map* m = map_create(0, 0, NULL);
  int val = 100;
  cr_assert(map_set_cstr(m, "", &val, sizeof(val), 0, NULL));
  cr_assert(map_remove_cstr(m, ""));
  size_t out;
  cr_assert_null(map_get_cstr(m, "", &out));
  map_free(m);
}
