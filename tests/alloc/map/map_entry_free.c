/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_entry_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:48:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 17:48:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "42/alloc/map.h"
#include "42/alloc/map.int.h"

static int freed_k;
static int freed_v;
static void fk(void* p) {
  (void)p;
  freed_k++;
}
static void fv(void* p) {
  (void)p;
  freed_v++;
}

Test(map_entry_free, unowned_does_not_call_destructors) {
  t_map_entry e = {0};
  freed_k = freed_v = 0;
  map_entry_free(&e);
  cr_assert_eq(freed_k, 0);
  cr_assert_eq(freed_v, 0);
}

Test(map_entry_free, owned_key_calls_destructor) {
  t_map_entry e = {
      .key = strdup("kk"), .key_size = 3, .owned = MAP_OWN_KEY, .del_key = fk};
  freed_k = 0;
  map_entry_free(&e);
  cr_assert_eq(freed_k, 1);
}

Test(map_entry_free, owned_value_calls_destructor) {
  t_map_entry e = {.value = strdup("vv"),
                   .value_size = 3,
                   .owned = MAP_OWN_VALUE,
                   .del_value = fv};
  freed_v = 0;
  map_entry_free(&e);
  cr_assert_eq(freed_v, 1);
}

Test(map_entry_free, owned_both_calls_both_destructors) {
  t_map_entry e = {.key = strdup("kk"),
                   .key_size = 3,
                   .value = strdup("vv"),
                   .value_size = 3,
                   .owned = MAP_OWN_BOTH,
                   .del_key = fk,
                   .del_value = fv};
  freed_k = freed_v = 0;
  map_entry_free(&e);
  cr_assert_eq(freed_k, 1);
  cr_assert_eq(freed_v, 1);
}
