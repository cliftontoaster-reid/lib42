/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:46:15 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:05:37 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

/**
 * @brief Copy n bytes from memory area src to memory area dest.
 *
 * The memory areas must not overlap. If they do, the behavior is undefined.
 * This function behaves like the standard memcpy: it performs a direct
 * byte-wise copy and returns dest.
 *
 * @param dest Destination buffer where bytes will be copied to.
 * @param src Source buffer to copy bytes from.
 * @param n Number of bytes to copy.
 * @return Pointer to dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copy n bytes from src to dest, safely handling overlapping areas.
 *
 * Unlike ft_memcpy, this function is safe when dest and src overlap. It
 * guarantees that the copy behaves as if the bytes from src are first copied
 * to a temporary area and then to dest.
 *
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param n Number of bytes to copy.
 * @return Pointer to dest.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fill the first n bytes of the memory area pointed to by s with the
 * specified byte value c (converted to unsigned char).
 *
 * @param s Pointer to the memory area to fill.
 * @param c Value to be set (interpreted as unsigned char).
 * @param n Number of bytes to set.
 * @return Pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Zero the first n bytes of the memory area pointed to by s.
 *
 * Equivalent to ft_memset(s, 0, n).
 *
 * @param s Pointer to the memory area to zero.
 * @param n Number of bytes to zero.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Scan the initial n bytes of the memory area pointed to by s for the
 * first occurrence of byte c (converted to unsigned char).
 *
 * @param s Pointer to the memory area to scan.
 * @param c Byte value to search for (interpreted as unsigned char).
 * @param n Number of bytes to examine.
 * @return Pointer to the located byte within s, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compare the first n bytes of the memory areas s1 and s2.
 *
 * The comparison is performed lexicographically on unsigned char values.
 *
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if the first
 *         n bytes of s1 are found, respectively, to be less than, to match,
 *         or be greater than the first n bytes of s2.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copy bytes from src to dest, stopping when byte c is found or n
 * bytes have been copied.
 *
 * If the byte c is found in src within the
 * first n bytes, copying stops after and including that byte and a pointer to
 * the byte following the copied c in dest is returned. Otherwise, n bytes
 * are copied and NULL is returned.
 *
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param c Byte value to stop at.
 * @param n Maximum number of bytes to copy.
 * @return Pointer to the byte after the copied c in dest, or NULL if c was
 *         not found in the first n bytes of src.
 */
void	*ft_memccpy(void *dest, const void *src, unsigned char c, size_t n);

/**
 * @brief Scan the initial n bytes of the memory area pointed to by s for the
 * last occurrence of byte c (converted to unsigned char).
 *
 * The search is performed from the end of the examined range towards the
 * beginning.
 *
 * @param s Pointer to the memory area to scan.
 * @param c Byte value to search for (interpreted as unsigned char).
 * @param n Number of bytes to examine.
 * @return Pointer to the located byte within s, or NULL if not found.
 */
void	*ft_memrchr(const void *s, int c, size_t n);

/**
 * @brief Search for the first occurrence of the byte sequence needle of
 * length needlelen in the memory area haystack of length haystacklen.
 *
 * This function is analogous to strstr but operates on arbitrary memory
 * buffers (may contain binary data and zeros). If needlelen is zero,
 * haystack is returned.
 *
 * @param haystack Buffer to search in.
 * @param haystacklen Length of haystack in bytes.
 * @param needle Sequence to search for.
 * @param needlelen Length of needle in bytes.
 * @return Pointer to the beginning of the first occurrence of needle in
 *         haystack, or NULL if not found.
 */
void	*ft_memmem(const void *haystack, size_t haystacklen, const void *needle,
			size_t needlelen);

/**
 * @brief Copy n bytes from src to dest and return a pointer to the byte
 * following the last written byte (i.e. dest + n).
 *
 * This behaves like ft_memcpy but returns dest + n instead of dest. The
 * memory areas must not overlap.
 *
 * @param dest Destination buffer.
 * @param src Source buffer.
 * @param n Number of bytes to copy.
 * @return Pointer to dest + n.
 */
void	*ft_mempcpy(void *dest, const void *src, size_t n);