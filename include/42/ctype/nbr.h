/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:17:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 15:23:10 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

/**
 * @brief Convert a string to a signed 8-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to int8_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstoi8(const char* str, int8_t* out);

/**
 * @brief Convert a string to an unsigned 8-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to uint8_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstou8(const char* str, uint8_t* out);

/**
 * @brief Convert a string to a signed 16-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to int16_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstoi16(const char* str, int16_t* out);

/**
 * @brief Convert a string to an unsigned 16-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to uint16_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstou16(const char* str, uint16_t* out);

/**
 * @brief Convert a string to a signed 32-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to int32_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstoi32(const char* str, int32_t* out);

/**
 * @brief Convert a string to an unsigned 32-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to uint32_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstou32(const char* str, uint32_t* out);

/**
 * @brief Convert a string to a signed 64-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to int64_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstoi64(const char* str, int64_t* out);

/**
 * @brief Convert a string to an unsigned 64-bit integer.
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to uint64_t to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstou64(const char* str, uint64_t* out);

/**
 * @brief Convert a string to a signed int (platform default size).
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to int to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstonbr(const char* str, int* out);

/**
 * @brief Convert a string to an unsigned int (platform default size).
 *
 * Parses the null-terminated string \p str and stores the result in \p out.
 * Returns true on successful conversion, false otherwise (invalid input or
 * out-of-range).
 *
 * @param str Null-terminated string representing a number.
 * @param out Pointer to unsigned int to store the result.
 * @return true if conversion succeeded, false otherwise.
 */
bool cstounbr(const char* str, unsigned int* out);

/**
 * @brief Convert a signed 8-bit integer to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Signed 8-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_i8(int8_t n);

/**
 * @brief Convert an unsigned 8-bit integer to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Unsigned 8-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_u8(uint8_t n);

/**
 * @brief Convert a signed 16-bit integer to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Signed 16-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_i16(int16_t n);

/**
 * @brief Convert an unsigned 16-bit integer to a newly allocated decimal
 * string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Unsigned 16-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_u16(uint16_t n);

/**
 * @brief Convert a signed 32-bit integer to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Signed 32-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_i32(int32_t n);

/**
 * @brief Convert an unsigned 32-bit integer to a newly allocated decimal
 * string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Unsigned 32-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_u32(uint32_t n);

/**
 * @brief Convert a signed 64-bit integer to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Signed 64-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_i64(int64_t n);

/**
 * @brief Convert an unsigned 64-bit integer to a newly allocated decimal
 * string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Unsigned 64-bit integer to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_u64(uint64_t n);

/**
 * @brief Convert a signed int to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Signed int to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_nbr(int n);

/**
 * @brief Convert an unsigned int to a newly allocated decimal string.
 *
 * Converts the value n to its decimal ASCII representation and returns a newly
 * allocated NUL-terminated string. Returns NULL on allocation failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param n Unsigned int to convert.
 * @return Newly allocated string representing n, or NULL on failure.
 */
char* cstr_unbr(unsigned int n);
