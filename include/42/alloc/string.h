/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:40:30 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 00:02:53 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "42/alloc/vec.h"

/**
 * @private Magic number to identify valid t_string instances.
 *
 * While not the most robust method, this magic number has been made
 * to be most likely never seen in a valid string data buffer.
 *
 * The simple presence of two non-consecutive printable characters, with
 * one of them being a null byte, makes it unlikely to appear in normal
 * string data that errors might expose.
 *
 * The value translates to the ASCII characters `S`, `\0`, `P`, and
 * `\x17`.
 *
 * @note If you do not trust this mechanism, or need every bit of performance,
 *     you can always avoid using functions that connect with your t_string
 *     or c strings directly. Such functions include \ref string_replace_cstr,
 *     \ref string_insert_cstr, \ref string_append_cstr, etc.
 */
#define STRING_MAGIC 0x53005017U

/**
 * @brief Variable-length string structure.
 *
 * Similar to other languages, \ref t_string represents a mutable,
 * dynamically resizable string. It maintains its own internal buffer,
 * size, and capacity to efficiently handle string operations.
 *
 * @note While it provides convenience functions for common string
 * manipulations, it is highly discouraged to manipulate the internal data
 * directly. More functions will be added later on if needed for you to
 * manipulate strings safely.
 */
typedef struct s_string {
  /// @privatesection

  /// @brief Magic number to identify valid t_string instances.
  ///
  /// This field is used internally to verify the integrity of the string
  /// instance.
  /// @warning Do not modify this field directly.
  /// @see STRING_MAGIC
  uint32_t magic;
  /// @brief Current capacity of the internal buffer.
  ///
  /// @note This capacity includes space for the null-terminator.
  ///
  /// @warning Do not modify this field directly. Use \ref string_reserve.
  ///          This is unlike \ref size, which may be modified to your
  ///          heart's content. As all of the functions made for t_string
  ///          will make sure to call \ref string_reserve as needed.
  size_t capacity;

  /// @publicsection

  /// @brief Current size of the string (number of valid characters).
  ///
  /// @note This size does not include the null-terminator. Meaning that
  ///       it is valid and safe to read until data[size], which will be
  ///       the null terminator. Unless you do use this in lua, unlikely as
  ///       that may be, where this would be considered out of bounds, as
  ///       lua strings do not need to be null-terminated, and indexes
  ///       start at 1, not 0.
  ///
  /// @warning Avoid modifying this field directly. It is safe to increase so,
  ///          and can cause unexpected behavior if you set it bellow the
  ///          actual size of the string. Considering the little benefits I
  ///          see in doing direct modification of this field, I highly
  ///          discourage it.
  size_t size;
  /// @brief Pointer to the internal character buffer.
  ///
  /// This buffer is null-terminated but may contain null bytes within the
  /// string data. The buffer is owned by the t_string instance and should
  /// not be modified directly.
  ///
  /// @warning While perfectly fine to modify the contents of this buffer,
  ///          as long as you do not move the position of the null terminator
  ///          or exceed the allocated capacity, it is highly discouraged to
  ///          manipulate this field directly. Use the provided string
  ///          functions to ensure correct behavior and to avoid memory
  ///          corruption. If needed however, please make ample use of
  ///          \ref string_reserve to ensure enough capacity before writing
  ///          to this buffer, as if the capacity was already enough, it will
  ///          avoid unnecessary reallocations, so should not be feared.
  char* data;
} t_string;

/**
 * @brief Create a new string from a C-style string.
 * @memberof s_string
 *
 * Allocates a new t_string and copies the contents of @p cstr into the
 * internal buffer. The returned string is null-terminated.
 *
 * @param cstr Source C-string to copy. May be NULL, in which case an empty
 *             string is returned.
 * @return Pointer to a newly allocated t_string on success, or NULL if
 *         allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          \ref string_free to avoid a memory leak.
 */
t_string* string_from(const char* cstr);

/**
 * @brief Allocate and initialize a new empty string.
 * @memberof s_string
 *
 * Creates a t_string with an empty buffer, size 0 and an initial capacity
 * suitable for subsequent appends.
 *
 * @return Pointer to a newly allocated t_string on success, or NULL if
 *         allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          \ref string_free to avoid a memory leak.
 */
t_string* string_new();

/**
 * @brief Append raw data to a t_string.
 * @memberof s_string
 *
 * Appends @p src bytes to the end of @p str. The function may reallocate
 * the internal buffer if needed to fit the additional data.
 *
 * @param str Pointer to the string to append to. Must not be NULL.
 * @param src Pointer to the data to append. Must not be NULL.
 * @return true on success, false if memory allocation fails or if @p str
 *         is NULL.
 */
bool string_append(t_string* str, const void* src);

/**
 * @brief Append a t_string to another t_string.
 * @memberof s_string
 *
 * This function appends all bytes of @p src to the end of @p str.
 * It behaves like `string_append(dest, src->data)` but is provided
 * for clarity and to handle the case where src and dest are the
 * same object.
 *
 * @param str Pointer to the string to append to. Must not be NULL.
 * @param src t_string to append. If NULL, this function behaves like
 *             appending an empty string and returns true.
 * @return true on success, false on memory allocation failure or if @p str
 *         is NULL.
 */
bool string_append_string(t_string* str, const t_string* src);

/**
 * @brief Append a C-style string to @p str.
 * @memberof s_string
 *
 * Appends the contents of @p cstr to the end of @p str. The function may
 * reallocate the internal buffer if needed to fit the additional data.
 *
 * @param str Pointer to the string to append to. Must not be NULL.
 * @param cstr C-style string to append. If NULL, this function behaves like
 *             appending an empty string and returns true.
 * @return true on success, false if memory allocation fails or if @p str
 *         is NULL.
 */
bool string_append_cstr(t_string* str, const char* cstr);

/**
 * @brief Prepend raw data to a t_string.
 * @memberof s_string
 *
 * Inserts @p src bytes at the beginning of @p str. The function may
 * reallocate the internal buffer if needed to fit the additional data.
 *
 * @param str Pointer to the string to modify. Must not be NULL.
 * @param src Pointer to the data to prepend. Must not be NULL.
 * @return true on success, false if memory allocation fails or if @p str
 *         is NULL.
 */
bool string_prepend(t_string* str, const void* src);

/**
 * @brief Prepend a t_string to another t_string.
 * @memberof s_string
 *
 * Inserts the contents of @p src at the beginning of the string @p str.
 * May reallocate the internal buffer to fit the new contents.
 *
 * @param str Pointer to the string to modify. Must not be NULL.
 * @param src t_string to insert at beginning. If NULL, this
 *             function behaves like prepending an empty string and returns
 *             true.
 *
 * @return true on success, false on memory allocation failure or if @p str
 *         is NULL.
 */
bool string_prepend_string(t_string* str, const t_string* src);

/**
 * @brief Prepend a C-style string to @p str.
 * @memberof s_string
 *
 * Inserts the contents of @p cstr at the beginning of the string @p str.
 * May reallocate the internal buffer to fit the new contents.
 *
 * @param str Pointer to the string to modify. Must not be NULL.
 * @param cstr C-style string to insert at beginning. If NULL, this
 *             function behaves like prepending an empty string and returns
 *             true.
 * @return true on success, false on memory allocation failure or if @p str
 *         is NULL.
 */
bool string_prepend_cstr(t_string* str, const char* cstr);

/**
 * @brief Free a string and its internal data.
 * @memberof s_string
 *
 * Frees the internal buffer and the t_string structure itself. Passing NULL
 * is a no-op.
 *
 * @param s Pointer to the string to free. May be NULL.
 */
void string_free(t_string* s);

/**
 * @brief Duplicate a string.
 * @memberof s_string
 *
 * Allocates a new t_string and copies the contents of @p s into it.
 *
 * @param s Pointer to the source string to clone. Must not be NULL.
 * @return Pointer to a newly allocated t_string with the same contents as
 *         @p s, or NULL if allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          \ref string_free to avoid leaks.
 */
t_string* string_clone(const t_string* s);

/**
 * @brief Ensure the string has at least @p min_capacity bytes of capacity.
 * @memberof s_string
 *
 * If the current capacity is less than @p min_capacity, this function
 * attempts to reallocate the internal buffer to at least the requested
 * capacity. If the capacity is already sufficient, the function does
 * nothing.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param min_capacity Minimum capacity to reserve.
 * @return true on success, false if reallocation fails or @p s is NULL.
 */
bool string_reserve(t_string* s, size_t min_capacity);

/**
 * @brief Shrink the string's capacity to fit its size.
 * @memberof s_string
 *
 * Attempts to reduce the string's capacity to the current size (plus the
 * terminating NUL if applicable) to free unused memory. May reallocate the
 * internal buffer.
 *
 * @param s Pointer to the string to shrink. Must not be NULL.
 * @return true on success or if no shrink is needed, false on allocation
 *         failure.
 */
bool string_shrink_to_fit(t_string* s);

/**
 * @brief Clear the contents of the string.
 * @memberof s_string
 *
 * Sets the string size to zero without releasing the capacity. The buffer
 * remains allocated so further appends may reuse it.
 *
 * @warning This function does erase the contents of the string buffer by
 *         zeroing it out.
 *
 * @param s Pointer to the string to clear. Must not be NULL.
 */
void string_clear(t_string* s);

/**
 * @brief Resize the string to @p new_size.
 * @memberof s_string
 *
 * If @p new_size is greater than the current size, the added bytes are
 * filled with @p fill. If @p new_size is smaller, the string is truncated.
 * The terminating NUL is updated appropriately where relevant.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param new_size New desired size.
 * @param fill Character used to fill if the string grows.
 * @return true on success, false if reallocation fails or @p s is NULL.
 */
bool string_resize(t_string* s, size_t new_size, char fill);

/**
 * @brief Append a single character to the end of the string.
 * @memberof s_string
 *
 * May reallocate the internal buffer to make room for the new character.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param c Character to append.
 * @return true on success, false if reallocation fails or @p s is NULL.
 */
bool string_push_char(t_string* s, char c);

/**
 * @brief Remove the last character from the string.
 * @memberof s_string
 *
 * If @p out is non-NULL, the removed character is stored at *out.
 * If the string is empty this function returns false and no character is
 * written.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param out Optional output pointer to receive the removed character.
 * @return true if a character was removed, false if the string was empty
 *         or @p s is NULL.
 */
bool string_pop_char(t_string* s, char* out);

/**
 * @brief Insert raw data into @p s at position @p pos.
 * @memberof s_string
 *
 * Characters from @p pos onward are shifted to make room for @p src.
 * If @p pos is greater than the string size, the insertion fails and the
 * function returns false.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Index at which to insert. Must be <= current string size.
 * @param src Pointer to the data to insert. Must not be NULL.
 * @return true on success, false if allocation fails, @p s is NULL or
 *         @p pos is out of bounds.
 */
bool string_insert(t_string* s, size_t pos, const void* src);

/**
 * @brief Insert a t_string into @p s at position @p pos.
 * @memberof s_string
 *
 * Characters from @p pos onward are shifted to make room for @p src.
 * If @p pos is greater than the string size, the insertion fails and the
 * function returns false.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Index at which to insert. Must be <= current string size.
 * @param src t_string to insert. If NULL it is treated as empty.
 * @return true on success, false if allocation fails, @p s is NULL or
 *         @p pos is out of bounds.
 */
bool string_insert_string(t_string* s, size_t pos, const t_string* src);

/**
 * @brief Insert a C-style string into @p s at position @p pos.
 * @memberof s_string
 *
 * Characters from @p pos onward are shifted to make room for @p cstr.
 * If @p pos is greater than the string size, the insertion fails and the
 * function returns false.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Index at which to insert. Must be <= current string size.
 * @param cstr C-style string to insert. If NULL it is treated as empty.
 * @return true on success, false if allocation fails, @p s is NULL or
 *         @p pos is out of bounds.
 */
bool string_insert_cstr(t_string* s, size_t pos, const char* cstr);

/**
 * @brief Erase a substring from @p s starting at @p pos of length @p len.
 * @memberof s_string
 *
 * Characters following the erased segment are shifted left to fill the
 * gap. If @p pos is out of bounds this returns false. If @p pos + @p len
 * goes beyond the end of the string, the function erases up to the end
 * of the string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position to begin erasing.
 * @param len Number of bytes to erase.
 * @return true on success, false if @p s is NULL or @p pos is out of
 *         bounds.
 */
bool string_erase(t_string* s, size_t pos, size_t len);

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p src.
 * @memberof s_string
 *
 * This is equivalent to erasing the substring and inserting @p src at
 * @p pos. The function may reallocate the buffer to accommodate the
 * resulting string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position where replacement begins.
 * @param len Length of the text to replace.
 * @param src Pointer to the data to insert in place of the erased text.
 * @return true on success, false if allocation fails, @p s is NULL, or
 *         @p pos is out of bounds.
 */
bool string_replace(t_string* s, size_t pos, size_t len, const void* src);

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p src.
 * @memberof s_string
 *
 * This is equivalent to erasing the substring and inserting @p src at
 * @p pos. The function may reallocate the buffer to accommodate the
 * resulting string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position where replacement begins.
 * @param len Length of the text to replace.
 * @param src t_string to insert in place of the erased text.
 * @return true on success, false if allocation fails, @p s is NULL, or
 *         @p pos is out of bounds.
 */
bool string_replace_string(t_string* s, size_t pos, size_t len,
                           const t_string* src);

/**
 * @brief Replace a substring of @p s starting at @p pos for length @p len
 * with @p cstr.
 * @memberof s_string
 *
 * This is equivalent to erasing the substring and inserting @p cstr at
 * @p pos. The function may reallocate the buffer to accommodate the
 * resulting string.
 *
 * @param s Pointer to the string to modify. Must not be NULL.
 * @param pos Position where replacement begins.
 * @param len Length of the text to replace.
 * @param cstr C-style string to insert in place of the erased text.
 * @return true on success, false if allocation fails, @p s is NULL, or
 *         @p pos is out of bounds.
 */
bool string_replace_cstr(t_string* s, size_t pos, size_t len, const char* cstr);

/**
 * @brief Create a new string containing a substring of @p s.
 * @memberof s_string
 *
 * Allocates a new t_string containing a copy of the substring starting
 * at @p pos and up to @p len bytes. If @p pos is out of bounds this
 * function returns NULL. If @p pos + @p len exceeds the string size the
 * substring is truncated to the end of the string.
 *
 * @param s Source string.
 * @param pos Starting index for the substring.
 * @param len Maximum length of the substring.
 * @return Pointer to a newly allocated t_string holding the substring or
 *         NULL if allocation fails or if @p pos is out of bounds.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          \ref string_free to avoid a memory leak.
 */
t_string* string_substr(const t_string* s, size_t pos, size_t len);

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle Pointer to the data to find. Must not be NULL.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find(const t_string* s, const void* needle, size_t start);

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle t_string substring to find. If needle is empty returns @p
 *               start.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find_string(const t_string* s, const t_string* needle,
                           size_t start);

/**
 * @brief Find the first occurrence of @p needle in @p s starting at
 * position @p start.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle C-style substring to find. If needle is empty returns @p
 *               start.
 * @param start Index from where the search should begin.
 * @return Index of the first occurrence of @p needle at or after @p start,
 *         or -1 if not found. Returns -1 if @p s or @p needle is NULL.
 */
ssize_t string_find_cstr(const t_string* s, const char* needle, size_t start);

/**
 * @brief Find the last occurrence of @p needle in @p s.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle Pointer to the data to find. Must not be NULL.
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind(const t_string* s, const void* needle);

/**
 * @brief Find the last occurrence of @p needle in @p s.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle t_string substring to find. If needle is empty returns the
 *               last valid index (i.e. s->size).
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind_string(const t_string* s, const t_string* needle);

/**
 * @brief Find the last occurrence of @p needle in @p s.
 * @memberof s_string
 *
 * @param s String to search in. Must not be NULL.
 * @param needle C-style substring to find. If needle is empty returns the
 *               last valid index (i.e. s->size).
 * @return Index of the last occurrence of @p needle, or -1 if not found.
 */
ssize_t string_rfind_cstr(const t_string* s, const char* needle);

/**
 * @brief Return true if the string @p s begins with @p prefix.
 * @memberof s_string
 *
 * @param s Source string. Must not be NULL.
 * @param prefix C-style prefix to check. If prefix is NULL or empty
 *               the function returns true.
 * @return true if @p s starts with @p prefix, false otherwise or if @p s
 *         or @p prefix is NULL.
 */
bool string_starts_with(const t_string* s, const char* prefix);

/**
 * @brief Return true if the string @p s ends with @p suffix.
 * @memberof s_string
 *
 * @param s Source string. Must not be NULL.
 * @param suffix C-style suffix to check. If suffix is NULL or empty the
 *               function returns true.
 * @return true if @p s ends with @p suffix, false otherwise or if @p s
 *         or @p suffix is NULL.
 */
bool string_ends_with(const t_string* s, const char* suffix);

/**
 * @brief Return a new string with leading and trailing characters removed.
 * @memberof s_string
 *
 * Characters contained in @p chars are trimmed from the beginning and
 * end of @p s. If @p chars is NULL the function trims standard
 * whitespace characters.
 *
 * @param s Source string. Must not be NULL.
 * @param chars Set of characters to remove from both ends.
 * @return Newly allocated t_string holding the trimmed contents or NULL
 *         on allocation failure.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_string and must free it using
 *          \ref string_free to avoid a memory leak.
 */
t_string* string_trim(const t_string* s, const char* chars);

/**
 * @brief Return a pointer to the string's internal, NUL-terminated buffer.
 * @memberof s_string
 *
 * The returned pointer points to the internal buffer of @p s and must not
 * be freed by the caller. The pointer remains valid until the string is
 * modified or freed.
 *
 * @param s Pointer to the string. Must not be NULL.
 * @return Pointer to a NUL-terminated C string. If @p s is NULL, or if the
 *         string is empty, returns NULL.
 */
char* string_cstr(t_string* s);

/**
 * @brief Compare two strings lexicographically.
 * @memberof s_string
 *
 * Returns an integer less than, equal to, or greater than zero if @p a is
 * found, respectively, to be less than, to match, or be greater than
 * @p b.
 *
 * @param a First string to compare.
 * @param b Second string to compare.
 * @return Negative value if a < b, zero if a == b, positive value if
 *         a > b.
 */
int string_cmp(const t_string* a, const t_string* b);

/**
 * @brief Return true if two strings are exactly equal.
 * @memberof s_string
 *
 * @param a First string.
 * @param b Second string.
 * @return true if both strings have the same size and identical contents,
 *         false otherwise.
 */
bool string_equals(const t_string* a, const t_string* b);

/**
 * @brief Case-insensitive lexicographic comparison of two strings.
 * @memberof s_string
 *
 * Similar to string_cmp but treats characters case-insensitively.
 *
 * @param a First string.
 * @param b Second string.
 * @return Negative value if a < b, zero if a == b, positive value if
 *         a > b when compared case-insensitively.
 */
int string_casecmp(const t_string* a, const t_string* b);

/**
 * @brief Format a string with printf-like semantics and store the result in @p
 * s.
 * @memberof s_string
 *
 * Writes formatted output into @p s, growing it as necessary. The function
 * follows printf formatting rules.
 *
 * @param s Pointer to the string to write into. Must not be NULL.
 * @param fmt printf-style format string.
 * @return true on success, false if memory allocation fails or @p s is NULL.
 */
bool string_format(t_string* s, const char* fmt, ...)
    __attribute__((format(printf, 2, 3)));

/**
 * @brief Split a string into a vector of substrings separated by @p sep.
 * @memberof s_string
 *
 * Returns a t_vec containing t_string* elements for each token. Empty
 * tokens are preserved (for consecutive separators). The caller takes
 * ownership of the returned vector and each t_string* inside it.
 *
 * @param s Source string to split. Must not be NULL.
 * @param sep Character used as the delimiter.
 * @return Pointer to a t_vec on success or NULL on allocation failure.
 * @warning This function allocates memory for the vector and each split
 *          element. The caller is responsible for freeing all elements
 *          and the vector itself to avoid memory leaks.
 */
t_vec* string_split(const t_string* s, char sep);

/**
 * @brief Lightweight runtime validation of a t_string pointer.
 * @memberof s_string
 *
 * Performs a quick, non-exhaustive check to determine if @p s appears to
 * be a valid t_string created by this library.
 *
 * @param s Pointer to test.
 * @return true if @p s appears to be a valid t_string created by the
 *         library; false otherwise.
 */
bool string_tagged(const void* s);