/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:10:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 13:20:53 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "42/alloc/map.h"
#include "macros.int.h"

/**
 * @brief Compare a key against an entry's key.
 * @internal
 *
 * Uses the map's custom comparator if set, otherwise falls back to
 * size comparison followed by memcmp.
 *
 * @param m The map (for access to the comparator).
 * @param entry The entry to compare against.
 * @param key The key to search for.
 * @param key_size Size of the key in bytes.
 * @return true if keys match, false otherwise.
 */
FT_INT bool map_key_cmp(const t_map* m, const t_map_entry* entry,
                        const void* key, size_t key_size);

/**
 * @brief Find an entry by key.
 * @internal
 *
 * Searches through the map's entries for a matching key.
 *
 * @param m The map to search.
 * @param key The key to search for.
 * @param key_size Size of the key in bytes.
 * @param out_prev If non-NULL, set to the list node before the found entry
 *                 (or NULL if the entry is the first node). Useful for removal.
 * @return Pointer to the list node containing the matching entry, or NULL if
 *         not found.
 */
FT_INT t_list* map_find_entry(t_map* m, const void* key, size_t key_size,
                              t_list** out_prev);

/**
 * @brief Free an entry's owned resources.
 * @internal
 *
 * Calls the appropriate destructors for owned key/value based on
 * the entry's ownership flags and destructor function pointers.
 *
 * @param entry The entry whose resources should be freed.
 */
FT_INT void map_entry_free(t_map_entry* entry);
