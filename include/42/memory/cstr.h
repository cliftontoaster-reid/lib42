/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:06:21 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 16:36:49 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

/**
 * @defgroup ft::cstr libft-like string manipulation functions
 * @brief A collection of functions for manipulating C-style strings.
 *
 * This namespace provides implementations of common string operations
 * similar to those found in the C standard library, with additional
 * functionality and safety features. Functions include string length
 * calculation, copying, concatenation, comparison, searching, duplication,
 * and trimming.
 */

/**
 * @brief Calculate the length of a null-terminated string.
 * @ingroup ft::cstr
 *
 * Counts bytes until the first '\0' is encountered. Equivalent to
 * the standard strlen(3).
 *
 * @param s Null-terminated input string.
 * @return Number of characters preceding the terminating null byte.
 */
size_t ft_strlen(const char* s);

/**
 * @brief Copy a null-terminated string from src to dest.
 * @ingroup ft::cstr
 *
 * The destination buffer must be large enough to receive the contents of src
 * including the terminating null byte. Returns dest.
 *
 * @param dest Destination buffer.
 * @param src Source null-terminated string.
 * @return Pointer to dest.
 */
char* ft_strcpy(char* dest, const char* src);

/**
 * @brief Copy up to n characters from src to dest.
 * @ingroup ft::cstr
 *
 * If src is less than n characters long, the remainder of dest will be
 * padded with '\0' bytes. If src is longer or equal to n, no terminating
 * '\0' is appended. This matches the behavior of the standard strncpy(3).
 *
 * @param dest Destination buffer.
 * @param src Source string.
 * @param n Maximum number of bytes to copy.
 * @return Pointer to dest.
 */
char* ft_strncpy(char* dest, const char* src, size_t n);

/**
 * @brief Append a null-terminated string src to the end of dest.
 * @ingroup ft::cstr
 *
 * The dest buffer must contain a null-terminated string and be large enough to
 * hold the result. The terminating null byte of dest is overwritten by the
 * first byte of src, and a new terminating null byte is appended.
 *
 * @param dest Destination buffer containing a null-terminated string.
 * @param src Source null-terminated string to append.
 * @return Pointer to dest.
 */
char* ft_strcat(char* dest, const char* src);

/**
 * @brief Append at most n characters from src to the end of dest.
 * @ingroup ft::cstr
 *
 * Ensures the result is null-terminated as long as dest had room for at least
 * one additional byte. Matches the behavior of strncat(3).
 *
 * @param dest Destination buffer containing a null-terminated string.
 * @param src Source string to append.
 * @param n Maximum number of characters to append from src.
 * @return Pointer to dest.
 */
char* ft_strncat(char* dest, const char* src, size_t n);

/**
 * @brief Append src to dest of total size 'size' (BSD strlcat semantics).
 * @ingroup ft::cstr
 *
 * Appends at most size - strlen(dest) - 1 bytes, null-terminating the result
 * (unless size <= strlen(dest)). Returns the total length of the string it
 * tried to create: initial strlen(dest) + strlen(src). This makes it easy to
 * detect truncation.
 *
 * @param dest Destination buffer containing a null-terminated string.
 * @param src Source string to append.
 * @param size Total size of the destination buffer in bytes.
 * @return The length of the string it tried to create (initial dest len + src
 *         len).
 */
size_t ft_strlcat(char* dest, const char* src, size_t size);

/**
 * @brief Compare two null-terminated strings lexicographically.
 * @ingroup ft::cstr
 *
 * Characters are compared as unsigned char values. Returns an integer less
 * than, equal to, or greater than zero if s1 is found, respectively, to be
 * less than, to match, or be greater than s2.
 *
 * @param s1 First null-terminated string.
 * @param s2 Second null-terminated string.
 * @return <0, 0, >0 as described above.
 */
int ft_strcmp(const char* s1, const char* s2);

/**
 * @brief Case-insensitive comparison of two null-terminated strings.
 * @ingroup ft::cstr
 *
 * Similar to ft_strcmp but treats characters case-insensitively.
 *
 * @param s1 First null-terminated string.
 * @param s2 Second null-terminated string.
 * @return <0, 0, >0 as described in ft_strcmp.
 */
int ft_casecmp(const char* s1, const char* s2);

/**
 * @brief Compare up to n bytes of two strings.
 * @ingroup ft::cstr
 *
 * Behaves like strncmp(3): compares at most n bytes of s1 and s2 as unsigned
 * char values. If n is zero, returns 0.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Maximum number of bytes to compare.
 * @return <0, 0, >0 as described in ft_strcmp.
 */
int ft_strncmp(const char* s1, const char* s2, size_t n);

/**
 * @brief Locate the first occurrence of character c in string s.
 * @ingroup ft::cstr
 *
 * The terminating '\0' is considered part of the string, so if c is '\0'
 * a pointer to the terminator is returned.
 *
 * @param s Null-terminated string to search.
 * @param c Character to find (converted to unsigned char).
 * @return Pointer to the located character in s, or NULL if not found.
 */
char* ft_strchr(const char* s, int c);

/**
 * @brief Locate the last occurrence of character c in string s.
 * @ingroup ft::cstr
 *
 * Behaves like strrchr(3).
 *
 * @param s Null-terminated string to search.
 * @param c Character to find (converted to unsigned char).
 * @return Pointer to the located character in s, or NULL if not found.
 */
char* ft_strrchr(const char* s, int c);

/**
 * @brief Find the first occurrence of the substring needle in haystack.
 * @ingroup ft::cstr
 *
 * Equivalent to strstr(3). If needle is an empty string, haystack is
 * returned.
 *
 * @param haystack String to search in.
 * @param needle Substring to search for.
 * @return Pointer to the first occurrence of needle in haystack, or NULL if
 *         not found.
 */
char* ft_strstr(const char* haystack, const char* needle);

/**
 * @brief Find the last occurrence of the substring needle in haystack.
 * @ingroup ft::cstr
 *
 * Not part of the C standard, but occasionally useful. Searches for the
 * rightmost occurrence of needle inside haystack and returns a pointer to its
 * beginning, or NULL if not found. If needle is empty, returns haystack +
 * strlen(haystack) (i.e. pointer to the terminator).
 *
 * @param haystack String to search.
 * @param needle Substring to search for.
 * @return Pointer to the beginning of the last occurrence, or NULL.
 */
char* ft_strrstr(const char* haystack, const char* needle);

/**
 * @brief Duplicate a null-terminated string by allocating memory and copying
 * its contents.
 * @ingroup ft::cstr
 *
 * The returned buffer must be freed by the caller. Returns NULL on allocation
 * failure.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param s Source null-terminated string.
 * @return Newly allocated copy of s, or NULL on failure.
 */
char* ft_strdup(const char* s);

/**
 * @brief Duplicate at most n bytes of a string, always null-terminating the
 * result (behaves like POSIX strndup).
 * @ingroup ft::cstr
 *
 * The returned buffer must be freed by the caller. If n is larger than the
 * length of s, only the bytes up to the terminating '\0' are copied.
 *
 * @warning The returned pointer must be freed by the caller to avoid memory
 * leaks.
 *
 * @param s Source string.
 * @param n Maximum number of bytes to copy from s.
 * @return Newly allocated, null-terminated string, or NULL on failure.
 */
char* ft_strndup(const char* s, size_t n);

/**
 * @brief Find the first character in s that matches any character in accept.
 * @ingroup ft::cstr
 *
 * Behaves like strpbrk(3).
 *
 * @param s String to search.
 * @param accept String containing characters to match.
 * @return Pointer to the first matching character in s, or NULL if none.
 */
char* ft_strpbrk(const char* s, const char* accept);

/**
 * @brief Return the length of the initial segment of s consisting entirely of
 * characters in accept.
 * @ingroup ft::cstr
 *
 * Matches the behavior of strspn(3).
 *
 * @param s Input string.
 * @param accept Characters to accept.
 * @return Length of the initial segment.
 */
size_t ft_strspn(const char* s, const char* accept);

/**
 * @brief Return the length of the initial segment of s consisting entirely of
 * characters not in reject.
 * @ingroup ft::cstr
 *
 * Matches the behavior of strcspn(3).
 *
 * @param s Input string.
 * @param reject Characters to reject.
 * @return Length of the initial segment not containing any reject chars.
 */
size_t ft_strcspn(const char* s, const char* reject);
