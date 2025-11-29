/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:36 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 23:54:33 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "macros.int.h"

/**
 * @brief Dynamic array (vector) structure.
 *
 * \ref t_vec represents a dynamically resizable array that can hold
 * elements of arbitrary types. It maintains its own internal buffer,
 * size, capacity, and element size to efficiently handle array operations.
 */
typedef struct s_vec {
  /// @privatesection

  /// @brief Current number of elements in the vector.
  ///
  /// Indicates how many elements are currently stored in the vector.
  ///
  /// @warning Do not modify this field directly. Use the provided vector
  ///          functions to ensure correct behavior and to avoid memory
  ///          corruption.
  size_t size;
  /// @brief Current capacity of the vector.
  ///
  /// Indicates how many elements the vector can hold before needing to
  /// reallocate its internal buffer.
  ///
  /// @warning Do not modify this field directly. Use the provided vector
  ///          functions to ensure correct behavior and to avoid memory
  ///          corruption.
  size_t capacity;
  /// @brief Size of each element in the vector.
  ///
  /// Indicates the size in bytes of each element stored in the vector.
  ///
  /// @warning Do not modify this field directly. It is set during vector
  ///          creation and should remain constant for the lifetime of
  ///          the vector. Editing this will always lead to undefined behavior.
  ///          If not undefined behavior in the most literal sense. As doing
  ///          so will de-align the internal buffer, and all further operations
  ///          on the vector will likely read or write out of bounds of the
  ///          element intended to be accessed, or even out of the buffer
  ///          itself.
  size_t elem_size;
  /// @brief Pointer to the internal data buffer.
  ///
  /// This buffer is owned by the t_vec instance and should not be modified
  /// directly. Use the provided vector functions to manipulate the data.
  ///
  /// @warning It is highly discouraged to manipulate the internal buffer
  ///          directly. Use the provided vector functions to ensure correct
  ///          behavior and to avoid memory corruption. I will be sincere
  ///          that this vec implementation is, less than ideal, and needs
  ///          improvements. Meaning that direct manipulation of this field
  ///          could very easily lead to memory corruption if you do not
  ///          know exactly what you are doing. So please, avoid it.
  void* data;
} t_vec;

/**
 * @brief Create a new dynamic array (vector).
 * @memberof s_vec
 *
 * Allocates and initializes a new t_vec to hold elements of size
 * @p elem_size.
 *
 * @param elem_size Size of each element in bytes. Must be greater than 0.
 * @return Pointer to a newly allocated t_vec on success, or NULL if
 *         allocation fails.
 * @warning This function allocates memory using malloc. The caller takes
 *          ownership of the returned t_vec and must free it using
 *          \ref vec_free to avoid memory leaks.
 */
t_vec* vec_create(size_t elem_size);

/**
 * @brief Append an element to the end of the vector.
 * @memberof s_vec
 *
 * Copies the object pointed to by @p elem into the vector's internal buffer
 * at the end (index == size). If necessary the vector will be resized.
 *
 * @param vec Pointer to the vector.
 * @param elem Pointer to the element to append. Must point to at least
 *             vec->elem_size bytes.
 * @return true on success, false on allocation failure or if @p vec or
 *         @p elem is NULL.
 */
bool vec_push_back(t_vec* vec, const void* elem);

/**
 * @brief Insert an element at the beginning of the vector.
 * @memberof s_vec
 *
 * Shifts existing elements up by one and copies @p elem into index 0.
 * The vector will be resized if required.
 *
 * @param vec Pointer to the vector.
 * @param elem Pointer to the element to insert. Must point to at least
 *             vec->elem_size bytes.
 * @return true on success, false on allocation failure or invalid args.
 */
bool vec_push_front(t_vec* vec, const void* elem);

/**
 * @brief Remove the last element from the vector.
 * @memberof s_vec
 *
 * Decrements the vector size. Does not reallocate the internal buffer.
 *
 * @param vec Pointer to the vector.
 * @return true if an element was removed, false if the vector was NULL or
 *         already empty.
 */
bool vec_pop_back(t_vec* vec);

/**
 * @brief Remove the first element from the vector.
 * @memberof s_vec
 *
 * Shifts remaining elements down by one and decrements the size. Does not
 * reallocate the internal buffer.
 *
 * @param vec Pointer to the vector.
 * @return true if an element was removed, false if the vector was NULL or
 *         already empty.
 */
bool vec_pop_front(t_vec* vec);

/**
 * @brief Get a pointer to the element at @p index.
 * @memberof s_vec
 *
 * Returns a pointer to the element stored at @p index within the vector's
 * internal buffer. The pointer is valid until the vector is modified
 * (reallocated or elements moved).
 *
 * @param vec Pointer to the vector.
 * @param index Zero-based index of the element to retrieve.
 * @return Pointer to the element on success, or NULL if @p vec is NULL or
 *         @p index is out of range.
 */
void* vec_get(const t_vec* vec, size_t index);

/**
 * @brief Replace the element at @p index with the object pointed by @p elem.
 * @memberof s_vec
 *
 * Copies vec->elem_size bytes from @p elem into the vector at the given
 * index.
 *
 * @param vec Pointer to the vector.
 * @param index Zero-based index of the element to replace.
 * @param elem Pointer to the new element data. Must point to at least
 *             vec->elem_size bytes.
 * @return true on success, false if @p vec is NULL, @p index is out of range,
 *         or @p elem is NULL.
 */
bool vec_set(t_vec* vec, size_t index, const void* elem);

/**
 * @brief Free the vector and its internal buffer.
 * @memberof s_vec
 *
 * Frees any allocated memory used by the vector and then frees the
 * t_vec structure itself. Passing NULL is a no-op.
 *
 * @param vec Pointer to the vector to free.
 */
void vec_free(t_vec* vec);

/**
 * @brief Resize the vector's internal buffer.
 * @private
 * @memberof s_vec
 *
 * Changes the capacity of the vector to @p new_capacity. If the new capacity
 * is smaller than the current size, the size is adjusted accordingly.
 *
 * @param vec Pointer to the vector.
 * @param new_capacity The new capacity for the vector.
 * @return true on success, false on allocation failure or if @p vec is NULL.
 */
FT_INT bool vec_resize(t_vec* vec, size_t new_capacity);