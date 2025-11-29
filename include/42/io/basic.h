/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:00:19 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/20 11:41:56 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include "42/alloc/string.h"

/**
 * @defgroup io::write I/O Output Functions
 * @ingroup io
 * @brief Input/Output functions
 *
 * The IO group provides a set of low-level functions for writing data to
 * file descriptors. It supports outputting characters, strings, integers
 * (signed/unsigned), hexadecimal values, pointers, floating-point numbers, and
 * raw bytes. All functions return the number of bytes written or -1 on error,
 * making them suitable for robust I/O operations in C programs.
 */

/**
 * @param fd The file descriptor to write to.
 * @param c The character to write.
 * @param n The number of times to write the character.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_nchar(int fd, char c, size_t n);

/**
 * @brief Writes a C-style string to the specified file descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param str The string to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_cstr(int fd, const char* str);

/**
 * @brief Writes a \ref t_string to the specified file descriptor.
 * @ingroup io::write
 * @relates t_string
 * @param fd The file descriptor to write to.
 * @param str The \ref t_string to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_cstring(int fd, const t_string* str);

/**
 * @brief Writes up to n characters from the C-style string to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param str The string to write from.
 * @param n The maximum number of characters to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_ncstr(int fd, const char* str, size_t n);

/**
 * @brief Writes a signed 64-bit integer as a string to the file descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The integer to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_int(int fd, int64_t n);

/**
 * @brief Writes an unsigned 64-bit integer as a string to the file descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The unsigned integer to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_uint(int fd, uint64_t n);

/**
 * @brief Writes an unsigned 64-bit integer in hexadecimal format to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The unsigned integer to write in hex.
 * @param uppercase If true, uses uppercase letters (A-F); otherwise, lowercase
 * (a-f).
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_hex(int fd, uint64_t n, bool uppercase);

/**
 * @brief Writes the pointer address in hexadecimal format to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param ptr The pointer whose address to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_ptr(int fd, const void* ptr);

/**
 * @brief Writes a float as a string with specified precision to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The float to write.
 * @param precision The number of decimal places to include.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_float(int fd, float n, size_t precision);

/**
 * @brief Writes a double as a string with specified precision to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The double to write.
 * @param precision The number of decimal places to include.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_double(int fd, double n, size_t precision);

/**
 * @brief Writes a long double as a string with specified precision to the file
 * descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param n The long double to write.
 * @param precision The number of decimal places to include.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_ldouble(int fd, long double n, size_t precision);

/**
 * @brief Writes n bytes from the buffer to the file descriptor.
 * @ingroup io::write
 * @param fd The file descriptor to write to.
 * @param buf The buffer to write from.
 * @param n The number of bytes to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t io_push_nbytes(int fd, const void* buf, size_t n);
