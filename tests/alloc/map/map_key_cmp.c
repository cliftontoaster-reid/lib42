/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_key_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:40:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 17:40:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/alloc/map.h"
#include "42/alloc/map.int.h"

static int my_cmp(const void* a, size_t a_sz, const void* b, size_t b_sz) {
  (void)a_sz;
  (void)b_sz;
  return strcmp((const char*)a, (const char*)b);
}

Test(map_key_cmp, size_mismatch_returns_false) {
  t_map m = {0};
  t_map_entry e = {.key = "abc", .key_size = 3};
  cr_assert_not(map_key_cmp(&m, &e, "ab", 2));
}

Test(map_key_cmp, memcmp_matches_returns_true) {
  t_map m = {0};
  t_map_entry e = {.key = "hello", .key_size = 6};
  cr_assert(map_key_cmp(&m, &e, "hello", 6));
}

Test(map_key_cmp, custom_cmp_used_when_present) {
  t_map m = {.cmp = my_cmp};
  t_map_entry e = {.key = "foo", .key_size = 4};
  cr_assert(map_key_cmp(&m, &e, "foo", 4));
}
