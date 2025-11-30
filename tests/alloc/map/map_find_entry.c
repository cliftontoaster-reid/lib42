/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:00:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 18:00:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/alloc/list.h"
#include "42/alloc/map.h"
#include "42/alloc/map.int.h"

Test(map_find_entry, find_entry_empty_returns_null) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  t_list* prev = NULL;
  t_list* n = map_find_entry(m, "does-not-exist", 15, &prev);
  cr_assert_null(n);
  cr_assert_null(prev);
  map_free(m);
}

Test(map_find_entry, find_entry_returns_node_and_prev) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, k2 = 2, v = 0;
  cr_assert(map_set(m, &k1, sizeof(k1), &v, sizeof(v), 0, NULL, NULL));
  cr_assert(map_set(m, &k2, sizeof(k2), &v, sizeof(v), 0, NULL, NULL));
  t_list* prev = NULL;
  /* search for k2 */
  t_list* found = map_find_entry(m, &k2, sizeof(k2), &prev);
  cr_assert_not_null(found);
  /* Prev may be NULL if insertion uses add_front. Adjust accordingly. */
  if (prev != NULL) {
    t_map_entry* prev_e = prev->content;
    cr_assert_eq(*((int*)prev_e->key), k1);
  } else {
    /* If prev is NULL, found is first and next must be k1 */
    cr_assert_not_null(found->next);
    t_map_entry* next_e = found->next->content;
    cr_assert_eq(*((int*)next_e->key), k1);
  }
  map_free(m);
}
