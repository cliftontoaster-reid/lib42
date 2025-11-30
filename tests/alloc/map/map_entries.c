/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_entries.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:05:00 by lfiorell           #+#    #+# */
/*   Updated: 2025/11/30 17:05:00 by lfiorell          ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/alloc/list.h"
#include "42/alloc/map.h"

Test(map_entries, entries_null_for_empty_map) {
  t_map* m = map_create(0, 0, NULL);
  cr_assert_null(map_entries(m));
  map_free(m);
}

Test(map_entries, entries_return_list_of_map_entries) {
  t_map* m = map_create(sizeof(int), sizeof(int), NULL);
  int k1 = 1, k2 = 2, v = 0;
  cr_assert(map_set(m, &k1, sizeof(k1), &v, sizeof(v), 0, NULL, NULL));
  cr_assert(map_set(m, &k2, sizeof(k2), &v, sizeof(v), 0, NULL, NULL));
  const t_list* entries = map_entries(m);
  cr_assert_not_null(entries);
  int count = 0;
  for (const t_list* n = entries; n; n = n->next) {
    t_map_entry* e = n->content;
    cr_assert_not_null(e);
    cr_assert_eq(e->value_size, sizeof(v));
    count++;
  }
  cr_assert_eq(count, (int)map_size(m));
  map_free(m);
}
