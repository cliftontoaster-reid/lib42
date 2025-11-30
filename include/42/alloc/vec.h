/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:56:36 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/30 15:18:06 by lfiorell         ###   ########.fr       */
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
 * Allocates and initializes a new t_vec to hold elements of size @p elem_size.
 * The vector starts with size 0 and a small initial capacity.
 *
 * @param elem_size Size of each element in bytes. Must be greater than 0.
 *
 * @return Pointer to a newly allocated t_vec on success, or NULL if
 *         allocation fails.
 *
 * @warning The caller owns the returned t_vec and must free it using
 *          vec_free() to avoid memory leaks.
 *
 * @par Example
 * @code
 * // Vector of integers
 * t_vec* ints = vec_create(sizeof(int));
 *
 * // Vector of pointers
 * t_vec* ptrs = vec_create(sizeof(void*));
 *
 * // Vector of custom structs
 * typedef struct { int x, y; } Point;
 * t_vec* points = vec_create(sizeof(Point));
 * @endcode
 */
t_vec* vec_create(size_t elem_size);

/**
 * @brief Append an element to the end of the vector.
 * @memberof s_vec
 *
 * Copies the object pointed to by @p elem into the vector at the end.
 * The vector is automatically resized if necessary.
 *
 * @param vec Pointer to the vector.
 * @param elem Pointer to the element to append.
 *
 * @return true on success, false on allocation failure or invalid arguments.
 *
 * @par Example
 * @code
 * t_vec* nums = vec_create(sizeof(int));
 *
 * int a = 10, b = 20, c = 30;
 * vec_push_back(nums, &a);
 * vec_push_back(nums, &b);
 * vec_push_back(nums, &c);
 * // nums: [10, 20, 30]
 *
 * // Inline push
 * vec_push_back(nums, &(int){40});
 * // nums: [10, 20, 30, 40]
 * @endcode
 */
bool vec_push_back(t_vec* vec, const void* elem);

/**
 * @brief Insert an element at the beginning of the vector.
 * @memberof s_vec
 *
 * Shifts existing elements up by one position and copies @p elem into index 0.
 * The vector is automatically resized if necessary.
 *
 * @param vec Pointer to the vector.
 * @param elem Pointer to the element to insert.
 *
 * @return true on success, false on allocation failure or invalid arguments.
 *
 * @note This operation is O(n) as all elements must be shifted.
 *
 * @par Example
 * @code
 * t_vec* v = vec_create(sizeof(int));
 * vec_push_back(v, &(int){2});
 * vec_push_back(v, &(int){3});
 * // v: [2, 3]
 *
 * vec_push_front(v, &(int){1});
 * // v: [1, 2, 3]
 * @endcode
 */
bool vec_push_front(t_vec* vec, const void* elem);

/**
 * @brief Remove the last element from the vector.
 * @memberof s_vec
 *
 * Decrements the vector size by one. The element is not zeroed; its memory
 * remains in the buffer until overwritten. Does not shrink the capacity.
 *
 * @param vec Pointer to the vector.
 *
 * @return true if an element was removed, false if the vector was NULL or
 *         already empty.
 *
 * @par Example
 * @code
 * // Get and remove last element
 * if (v->size > 0) {
 *   int* last = vec_get(v, v->size - 1);
 *   int value = *last;
 *   vec_pop_back(v);
 *   printf("Popped: %d\n", value);
 * }
 * @endcode
 */
bool vec_pop_back(t_vec* vec);

/**
 * @brief Remove the first element from the vector.
 * @memberof s_vec
 *
 * Shifts remaining elements down by one position and decrements the size.
 * Does not shrink the capacity.
 *
 * @param vec Pointer to the vector.
 *
 * @return true if an element was removed, false if the vector was NULL or
 *         already empty.
 *
 * @note This operation is O(n) as all elements must be shifted.
 *
 * @par Example
 * @code
 * // Process elements in FIFO order
 * while (v->size > 0) {
 *   int* first = vec_get(v, 0);
 *   process(*first);
 *   vec_pop_front(v);
 * }
 * @endcode
 */
bool vec_pop_front(t_vec* vec);

/**
 * @brief Get a pointer to the element at @p index.
 * @memberof s_vec
 *
 * Returns a pointer to the element at the specified index. The pointer is
 * valid until the vector is modified (resized or elements moved).
 *
 * @param vec Pointer to the vector.
 * @param index Zero-based index of the element to retrieve.
 *
 * @return Pointer to the element on success, or NULL if @p vec is NULL or
 *         @p index is out of range.
 *
 * @warning The returned pointer may become invalid after push/pop operations
 *          that trigger a reallocation.
 *
 * @par Example
 * @code
 * t_vec* v = vec_create(sizeof(int));
 * vec_push_back(v, &(int){100});
 * vec_push_back(v, &(int){200});
 *
 * int* elem = vec_get(v, 1);
 * printf("%d\n", *elem);  // prints 200
 *
 * // Modify in-place
 * *elem = 250;
 *
 * // Bounds checking
 * if (vec_get(v, 999) == NULL) {
 *   printf("Index out of range\n");
 * }
 * @endcode
 */
void* vec_get(const t_vec* vec, size_t index);

/**
 * @brief Replace the element at @p index.
 * @memberof s_vec
 *
 * Copies vec->elem_size bytes from @p elem into the vector at the given index,
 * overwriting the existing element.
 *
 * @param vec Pointer to the vector.
 * @param index Zero-based index of the element to replace.
 * @param elem Pointer to the new element data.
 *
 * @return true on success, false if @p vec is NULL, @p index is out of range,
 *         or @p elem is NULL.
 *
 * @par Example
 * @code
 * t_vec* v = vec_create(sizeof(int));
 * vec_push_back(v, &(int){1});
 * vec_push_back(v, &(int){2});
 * vec_push_back(v, &(int){3});
 * // v: [1, 2, 3]
 *
 * vec_set(v, 1, &(int){99});
 * // v: [1, 99, 3]
 * @endcode
 */
bool vec_set(t_vec* vec, size_t index, const void* elem);

/**
 * @brief Free the vector and its internal buffer.
 * @memberof s_vec
 *
 * Frees any allocated memory used by the vector and then frees the t_vec
 * structure itself. Passing NULL is a no-op.
 *
 * @param vec Pointer to the vector to free.
 *
 * @warning After calling this function, the vec pointer is invalid.
 *
 * @note If the vector contains pointers to dynamically allocated objects,
 *       you must free those objects manually before calling vec_free().
 *
 * @par Example
 * @code
 * t_vec* v = vec_create(sizeof(int));
 * // ... use vector ...
 * vec_free(v);
 * v = NULL;  // good practice
 *
 * // For vectors of pointers, free contents first:
 * t_vec* ptrs = vec_create(sizeof(char*));
 * vec_push_back(ptrs, &(char*){strdup("hello")});
 * vec_push_back(ptrs, &(char*){strdup("world")});
 *
 * for (size_t i = 0; i < ptrs->size; i++) {
 *   char** str = vec_get(ptrs, i);
 *   free(*str);
 * }
 * vec_free(ptrs);
 * @endcode
 */
void vec_free(t_vec* vec);

/**
 * @brief Resize the vector's internal buffer.
 * @memberof s_vec
 * @private
 *
 * Changes the capacity of the vector to @p new_capacity. If the new capacity
 * is smaller than the current size, the size is adjusted accordingly
 * (truncating elements).
 *
 * @param vec Pointer to the vector.
 * @param new_capacity The new capacity for the vector.
 *
 * @return true on success, false on allocation failure or if @p vec is NULL.
 *
 * @note This is an internal function. Normally you don't need to call it
 *       directly as push operations handle resizing automatically.
 */
FT_INT bool vec_resize(t_vec* vec, size_t new_capacity);