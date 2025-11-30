/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:58:30 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 15:12:46 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "42/alloc/list.h"

/**
 * @brief Ownership flags for map keys.
 * @memberof s_map_entry
 *
 * When `MAP_OWN_KEY` is set the map makes an internal copy of the key bytes
 * on insert and frees that copy when the entry is removed or when the map
 * is destroyed. The same applies for \ref MAP_OWN_VALUE and the value bytes.
 *
 * Use these flags when the map should own and manage the lifetime of
 * sized or variable-length data (for example duplicated strings). If the
 * flags are not set the map stores the caller pointer as-is — the caller
 * must ensure the memory remains valid for the entry's lifetime.
 */
#define MAP_OWN_KEY 1

/**
 * @brief Ownership flags for map values.
 * @memberof s_map_entry
 *
 * When `MAP_OWN_VALUE` is set the map makes an internal copy of the value
 * bytes on insert and frees that copy when the entry is removed or when the
 * map is destroyed. The same applies for \ref MAP_OWN_KEY and the key bytes.
 *
 * Use these flags when the map should own and manage the lifetime of
 * sized or variable-length data (for example duplicated strings). If the
 * flags are not set the map stores the caller pointer as-is — the caller
 * must ensure the memory remains valid for the entry's lifetime.
 */
#define MAP_OWN_VALUE 2

/**
 * @brief Ownership flags for map entries.
 * @memberof s_map_entry
 *
 * When `MAP_OWN_BOTH` is set the map makes an internal copy of the key and
 * value bytes on insert and frees that copy when the entry is removed or when
 * the map is destroyed.
 *
 * Use these flags when the map should own and manage the lifetime of
 * sized or variable-length data (for example duplicated strings). If the
 * flags are not set the map stores the caller pointer as-is — the caller
 * must ensure the memory remains valid for the entry's lifetime.
 */
#define MAP_OWN_BOTH (MAP_OWN_KEY | MAP_OWN_VALUE)

/**
 * @brief Map entry structure.
 * @relates s_map
 *
 * Each \ref t_map_entry holds a key-value pair along with metadata about
 * their sizes and ownership semantics.
 */
typedef struct s_map_entry {
  /// @publicsection

  /// @brief Pointer to the key bytes.
  ///
  /// This pointer may point to memory owned by the map or by the caller,
  /// depending on the ownership flags set for the entry.
  ///
  /// @warning If \ref MAP_OWN_KEY is not set, the caller is responsible for
  ///          ensuring the key memory remains valid for the lifetime of the
  ///          entry. Failure to do so may lead to undefined behavior when
  ///          accessing the key.
  void* key;
  /// @brief Size of the key in bytes.
  ///
  /// Indicates the length of the key data pointed to by \ref key.
  ///
  /// @warning For variable-length keys (e.g., strings), the caller must
  ///          ensure the size is accurate. As it is used for quick comparison
  ///          and lookup operations to filter out keys of different sizes. As a
  ///          comparison between keys is much more expensive than a simple size
  ///          check.
  size_t key_size;
  /// @brief Pointer to the value bytes.
  ///
  /// This pointer may point to memory owned by the map or by the caller,
  /// depending on the ownership flags set for the entry.
  ///
  /// @warning If \ref MAP_OWN_VALUE is not set, the caller is responsible for
  ///          ensuring the value memory remains valid for the lifetime of the
  ///          entry. Failure to do so may lead to undefined behavior when
  ///          accessing the value.
  void* value;
  /// @brief Size of the value in bytes.
  ///
  /// Indicates the length of the value data pointed to by \ref value.
  /// Or in other words, the full capacity of the mallocated block pointed to.
  ///
  /// @warning For variable-length values (e.g., strings), the caller must
  ///          ensure the size is accurate, as this may result in incomplete
  ///          compairaisons to undified behavior, if the size is smaller than
  ///          the actual size of the value, or too large, respectively.
  size_t value_size;
  /// @brief Ownership flags for the key and value.
  ///
  /// When \ref MAP_OWN_KEY is set the map owns the key bytes and will free
  /// them when the entry is removed or the map is destroyed. Similarly,
  /// when \ref MAP_OWN_VALUE is set the map owns the value bytes.
  ///
  /// @warning Improper management of ownership flags may lead to memory
  ///          leaks or double-free errors. Ensure that the flags accurately
  ///          reflect the ownership semantics intended for each entry.
  ///
  /// @see MAP_OWN_KEY
  /// @see MAP_OWN_VALUE
  /// @see MAP_OWN_BOTH
  int owned;
  void (*del_key)(void*);    // optional destructor for key
  void (*del_value)(void*);  // optional destructor for value
} t_map_entry;

/**
 * @brief Associative map (dictionary) structure.
 *
 * A simple key-value store allowing insertion, retrieval, and deletion of
 * entries based on keys. Keys and values can be of arbitrary sizes, and
 * ownership semantics can be specified for each entry.
 */
typedef struct s_map {
  /// @privatesection

  /// @brief List of map entries.
  t_list* entries;
  /// @brief Number of entries in the map.
  size_t size;
  /// @brief Default key size for entries.
  size_t default_key_size; /* 0 = variable */
  /// @brief Default value size for entries.
  size_t default_value_size; /* 0 = variable */
  /// @brief Comparison function for keys.
  int (*cmp)(const void*, size_t, const void*, size_t);
} t_map;

/* ************************************************************************** */
/*                                    Creation & Destruction                  */
/* ************************************************************************** */

/**
 * @brief Create a new map.
 * @memberof s_map
 *
 * Allocates and initializes a new map structure. The map starts empty with
 * no entries.
 *
 * @param default_key_size Default size for keys when using map_set_default().
 *                         Pass 0 for variable-sized keys.
 * @param default_value_size Default size for values when using
 *                           map_set_default(). Pass 0 for variable-sized
 *                           values.
 * @param cmp Optional custom comparison function for keys. If NULL, keys are
 *            compared using memcmp after a size check. The function should
 *            return 0 if keys are equal, non-zero otherwise.
 *            Signature: `int cmp(const void* a, size_t a_size,
 *                                const void* b, size_t b_size)`
 *
 * @return Pointer to the newly created map, or NULL on allocation failure
 *         (errno set to ENOMEM).
 *
 * @note The caller is responsible for freeing the map with map_free().
 *
 * @par Example
 * @code
 * // Map with fixed-size int keys and variable-size values
 * t_map* m = map_create(sizeof(int), 0, NULL);
 *
 * // Map with custom string comparison
 * int my_strcmp(const void* a, size_t a_sz, const void* b, size_t b_sz) {
 *   (void)a_sz; (void)b_sz;
 *   return strcmp((const char*)a, (const char*)b);
 * }
 * t_map* str_map = map_create(0, 0, my_strcmp);
 * @endcode
 */
t_map* map_create(size_t default_key_size, size_t default_value_size,
                  int (*cmp)(const void*, size_t, const void*, size_t));

/**
 * @brief Free a map and all its entries.
 * @memberof s_map
 *
 * Destroys the map, freeing all entries. For each entry, if ownership flags
 * are set, the corresponding destructor (or free()) is called on the owned
 * key/value.
 *
 * @param m The map to free. If NULL, this function does nothing.
 *
 * @warning After calling this function, the map pointer is invalid and must
 *          not be used.
 *
 * @see map_clear() to remove all entries without destroying the map itself.
 */
void map_free(t_map* m);

/**
 * @brief Remove all entries from a map.
 * @memberof s_map
 *
 * Clears all entries from the map, properly freeing owned keys and values
 * using their destructors. The map itself remains valid and can be reused.
 *
 * @param m The map to clear. If NULL, this function does nothing.
 *
 * @note After clearing, map_size() returns 0.
 *
 * @see map_free() to destroy the map entirely.
 */
void map_clear(t_map* m);

/* ************************************************************************** */
/*                                    Core Operations                         */
/* ************************************************************************** */

/**
 * @brief Insert or update a key-value pair in the map.
 * @memberof s_map
 *
 * If the key already exists, the existing value is replaced (and freed if
 * owned). If the key does not exist, a new entry is created.
 *
 * @param m The map to insert into.
 * @param key Pointer to the key bytes.
 * @param key_size Size of the key in bytes.
 * @param value Pointer to the value bytes.
 * @param value_size Size of the value in bytes.
 * @param owned_flags Ownership flags (MAP_OWN_KEY, MAP_OWN_VALUE, or
 *                    MAP_OWN_BOTH). When set, the map copies and owns the
 *                    corresponding data.
 * @param del_key Optional destructor for the key. Called instead of free()
 *                when the key is owned and needs to be freed. Pass NULL to
 *                use free().
 * @param del_value Optional destructor for the value. Called instead of free()
 *                  when the value is owned and needs to be freed. Pass NULL to
 *                  use free().
 *
 * @return true on success, false on failure (errno set to EINVAL for invalid
 *         arguments, ENOMEM for allocation failure).
 *
 * @note When updating an existing key, ownership flags for the key are
 *       preserved; only value ownership is updated.
 *
 * @par Example
 * @code
 * // Store an integer value (not owned)
 * int x = 42;
 * map_set(m, "answer", 7, &x, sizeof(int), MAP_OWN_KEY, NULL, NULL);
 *
 * // Store a duplicated string value (owned)
 * map_set(m, "greeting", 9, "hello", 6, MAP_OWN_BOTH, NULL, NULL);
 *
 * // Store a complex struct with custom destructor
 * t_widget* w = widget_create();
 * map_set(m, &id, sizeof(id), w, sizeof(*w), MAP_OWN_VALUE, NULL, widget_free);
 * @endcode
 */
bool map_set(t_map* m, const void* key, size_t key_size, const void* value,
             size_t value_size, int owned_flags, void (*del_key)(void*),
             void (*del_value)(void*));

/**
 * @brief Insert or update using default sizes and ownership.
 * @memberof s_map
 *
 * Convenience function that uses the map's default_key_size and
 * default_value_size set at creation. Always uses MAP_OWN_BOTH and free()
 * as the destructor.
 *
 * @param m The map to insert into.
 * @param key Pointer to the key bytes.
 * @param value Pointer to the value bytes.
 *
 * @return true on success, false on failure (errno set to EINVAL if default
 *         sizes are 0, ENOMEM for allocation failure).
 *
 * @note This function requires that both default_key_size and
 *       default_value_size were set to non-zero values at map creation.
 *
 * @par Example
 * @code
 * // Create map with fixed sizes
 * t_map* m = map_create(sizeof(int), sizeof(double), NULL);
 *
 * int key = 1;
 * double val = 3.14;
 * map_set_default(m, &key, &val);
 * @endcode
 */
int map_set_default(t_map* m, const void* key, const void* value);

/**
 * @brief Retrieve a value by key.
 * @memberof s_map
 *
 * Searches for an entry with the specified key and returns a pointer to its
 * value.
 *
 * @param m The map to search.
 * @param key Pointer to the key bytes to search for.
 * @param key_size Size of the key in bytes.
 * @param[out] out_value_size If non-NULL, receives the size of the returned
 *                            value in bytes. Set to 0 if key is not found.
 *
 * @return Pointer to the value if found, NULL otherwise (errno set to EINVAL
 *         for invalid arguments, not set if simply not found).
 *
 * @warning The returned pointer is valid only as long as the entry remains
 *          in the map. Do not free it directly.
 *
 * @par Example
 * @code
 * size_t val_size;
 * int* val = map_get(m, "count", 6, &val_size);
 * if (val != NULL) {
 *   printf("count = %d (size: %zu)\n", *val, val_size);
 * }
 * @endcode
 */
void* map_get(t_map* m, const void* key, size_t key_size,
              size_t* out_value_size);

/**
 * @brief Remove an entry by key.
 * @memberof s_map
 *
 * Searches for and removes the entry with the specified key. If found, the
 * entry is removed and owned resources are freed using their destructors.
 *
 * @param m The map to remove from.
 * @param key Pointer to the key bytes to search for.
 * @param key_size Size of the key in bytes.
 *
 * @return true if the entry was found and removed, false otherwise (errno
 *         set to EINVAL for invalid arguments, ENOENT if key not found).
 *
 * @par Example
 * @code
 * if (!map_remove(m, "obsolete", 9)) {
 *   if (errno == ENOENT)
 *     printf("Key not found\n");
 * }
 * @endcode
 */
int map_remove(t_map* m, const void* key, size_t key_size);

/* ************************************************************************** */
/*                                    C-String Convenience                    */
/* ************************************************************************** */

/**
 * @brief Insert or update using a C-string key.
 * @memberof s_map
 *
 * Convenience function for string keys. The key is always copied (MAP_OWN_KEY
 * is forced). The null terminator is included in the key size.
 *
 * @param m The map to insert into.
 * @param key_cstr Null-terminated string key.
 * @param value Pointer to the value bytes.
 * @param value_size Size of the value in bytes.
 * @param owned_flags Ownership flags for the value (MAP_OWN_KEY is always
 *                    added internally).
 * @param del_value Optional destructor for the value.
 *
 * @return true on success, false on failure.
 *
 * @par Example
 * @code
 * int count = 10;
 * map_set_cstr(m, "items", &count, sizeof(count), 0, NULL);
 *
 * char* name = strdup("Alice");
 * map_set_cstr(m, "user", name, strlen(name) + 1, MAP_OWN_VALUE, NULL);
 * @endcode
 */
int map_set_cstr(t_map* m, const char* key_cstr, const void* value,
                 size_t value_size, int owned_flags, void (*del_value)(void*));

/**
 * @brief Retrieve a value by C-string key.
 * @memberof s_map
 *
 * Convenience function for string keys. Searches for an entry with the
 * specified null-terminated string key.
 *
 * @param m The map to search.
 * @param key_cstr Null-terminated string key to search for.
 * @param[out] out_value_size If non-NULL, receives the size of the value.
 *
 * @return Pointer to the value if found, NULL otherwise.
 *
 * @par Example
 * @code
 * int* count = map_get_cstr(m, "items", NULL);
 * if (count != NULL) {
 *   printf("items = %d\n", *count);
 * }
 * @endcode
 */
void* map_get_cstr(t_map* m, const char* key_cstr, size_t* out_value_size);

/**
 * @brief Remove an entry by C-string key.
 * @memberof s_map
 *
 * Convenience function for string keys. Removes the entry with the specified
 * null-terminated string key.
 *
 * @param m The map to remove from.
 * @param key_cstr Null-terminated string key to remove.
 *
 * @return true if found and removed, false otherwise.
 */
int map_remove_cstr(t_map* m, const char* key_cstr);

/* ************************************************************************** */
/*                                    Iteration & Queries                     */
/* ************************************************************************** */

/**
 * @brief Get the number of entries in the map.
 * @memberof s_map
 *
 * @param m The map to query. If NULL, returns 0.
 *
 * @return The number of key-value pairs in the map.
 *
 * @note This operation is O(1).
 */
size_t map_size(t_map* m);

/**
 * @brief Get read-only access to the entries list.
 * @memberof s_map
 *
 * Returns the internal linked list of entries for iteration. Each node's
 * content is a pointer to a t_map_entry.
 *
 * @param m The map to access.
 *
 * @return Pointer to the first node of the entries list, or NULL if empty.
 *
 * @warning Do not modify the list or its entries through this pointer.
 *          Use map_entries_mut() if mutation is needed.
 *
 * @par Example
 * @code
 * for (const t_list* n = map_entries(m); n; n = n->next) {
 *   const t_map_entry* e = n->content;
 *   printf("key_size=%zu, value_size=%zu\n", e->key_size, e->value_size);
 * }
 * @endcode
 */
const t_list* map_entries(t_map* m);

/**
 * @brief Get mutable access to the entries list.
 * @memberof s_map
 *
 * Returns the internal linked list of entries for direct manipulation.
 *
 * @param m The map to access.
 *
 * @return Pointer to the first node of the entries list, or NULL if empty.
 *
 * @warning Modifying entries directly can corrupt map state. Use with caution.
 *          Do not add/remove nodes without updating the map's size field.
 */
t_list* map_entries_mut(t_map* m);

/**
 * @brief Apply a function to each entry, collecting results.
 * @memberof s_map
 *
 * Iterates over all entries, calling the provided function on each. The
 * return values are collected into a new list.
 *
 * @param m The map to iterate over.
 * @param func Function to call on each entry. Receives the entry and the
 *             user-provided argument. Return value is added to result list.
 * @param arg User-provided argument passed to each function call.
 *
 * @return A new list containing all non-NULL return values from func, or
 *         NULL if the map is empty or all calls returned NULL.
 *
 * @note The caller is responsible for freeing the returned list.
 *
 * @par Example
 * @code
 * void* get_key(const t_map_entry* e, void* arg) {
 *   (void)arg;
 *   return e->key;  // Collect all keys
 * }
 * t_list* keys = map_foreach(m, get_key, NULL);
 * @endcode
 */
t_list* map_foreach(t_map* m,
                    void* (*func)(const t_map_entry* entry, void* arg),
                    void* arg);

/**
 * @brief Apply a function to each entry for side effects.
 * @memberof s_map
 *
 * Iterates over all entries, calling the provided function on each. Unlike
 * map_foreach(), this function does not collect results.
 *
 * @param m The map to iterate over.
 * @param func Function to call on each entry. Receives a mutable pointer
 *             to the entry and the user-provided argument.
 * @param arg User-provided argument passed to each function call.
 *
 * @par Example
 * @code
 * void print_entry(t_map_entry* e, void* arg) {
 *   (void)arg;
 *   printf("%s = ...\n", (char*)e->key);
 * }
 * map_map(m, print_entry, NULL);
 * @endcode
 */
void map_map(t_map* m, void (*func)(t_map_entry* entry, void* arg), void* arg);

/**
 * @brief Find an entry matching a predicate.
 * @memberof s_map
 *
 * Searches for the first entry for which the predicate returns true.
 *
 * @param m The map to search.
 * @param predicate Function that tests each entry. Should return true if
 *                  the entry matches, false otherwise.
 * @param arg User-provided argument passed to the predicate.
 *
 * @return Pointer to the first matching entry, or NULL if none found.
 *
 * @par Example
 * @code
 * bool has_large_value(const t_map_entry* e, void* arg) {
 *   size_t threshold = *(size_t*)arg;
 *   return e->value_size > threshold;
 * }
 * size_t min_size = 1024;
 * t_map_entry* large = map_find(m, has_large_value, &min_size);
 * @endcode
 */
t_map_entry* map_find(t_map* m,
                      bool (*predicate)(const t_map_entry* entry, void* arg),
                      void* arg);
