/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:06:41 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 15:06:51 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/alloc/map.h"

void map_map(t_map* m, void (*func)(t_map_entry* entry, void* arg), void* arg) {
  if (m == NULL || func == NULL) return;

  t_list* current = m->entries;

  while (current != NULL) {
    t_map_entry* entry = (t_map_entry*)current->content;
    func(entry, arg);
    current = current->next;
  }
}
