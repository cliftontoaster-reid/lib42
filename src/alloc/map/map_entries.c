/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_entries.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:59:04 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 14:59:33 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/map.h"

const t_list* map_entries(t_map* m) {
  if (m == NULL) return NULL;
  return m->entries;
}

t_list* map_entries_mut(t_map* m) {
  if (m == NULL) return NULL;
  return m->entries;
}
