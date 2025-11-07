/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctype.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:31:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:31:26 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Test for an alphabetic character.
 *
 * Returns true if the character is an upper- or lower-case letter (A-Z or
 * a-z). The function treats the argument as a plain character value; for
 * correct behavior with negative char types, callers should cast to unsigned
 * char first.
 *
 * @param c Character to test.
 * @return true if c is alphabetic, false otherwise.
 */
bool ft_isalpha(char c);

/**
 * @brief Test for a decimal digit character.
 *
 * Returns true if the character is one of '0'..'9'.
 *
 * @param c Character to test.
 * @return true if c is a decimal digit, false otherwise.
 */
bool ft_isdigit(char c);

/**
 * @brief Test for an alphanumeric character.
 *
 * Returns true if the character is alphabetic or a decimal digit.
 *
 * @param c Character to test.
 * @return true if c is alphanumeric, false otherwise.
 */
bool ft_isalnum(char c);

/**
 * @brief Test whether the character is an ASCII character (0..127).
 *
 * Returns true if the value of c is in the range of 7-bit ASCII (0 to 127).
 *
 * @param c Character to test.
 * @return true if c is a 7-bit ASCII character, false otherwise.
 */
bool ft_isascii(char c);

/**
 * @brief Test for any printable character including space.
 *
 * Returns true for characters with graphical representation or the space
 * character (i.e., characters with values between 0x20 and 0x7E inclusive
 * in the ASCII table).
 *
 * @param c Character to test.
 * @return true if c is printable (including space), false otherwise.
 */
bool ft_isprint(char c);

/**
 * @brief Test for white-space characters.
 *
 * Returns true for standard C whitespace characters: space, form-feed,
 * newline, carriage return, horizontal tab, and vertical tab.
 *
 * @param c Character to test.
 * @return true if c is a whitespace character, false otherwise.
 */
bool ft_isspace(char c);

/**
 * @brief Test for a lower-case alphabetic character.
 *
 * Returns true if the character is a lower-case letter ('a'..'z').
 *
 * @param c Character to test.
 * @return true if c is lower-case, false otherwise.
 */
bool ft_islower(char c);

/**
 * @brief Test for an upper-case alphabetic character.
 *
 * Returns true if the character is an upper-case letter ('A'..'Z').
 *
 * @param c Character to test.
 * @return true if c is upper-case, false otherwise.
 */
bool ft_isupper(char c);

/**
 * @brief Convert an upper-case letter to the corresponding lower-case.
 *
 * If c is an upper-case ASCII letter ('A'..'Z'), returns the corresponding
 * lower-case letter ('a'..'z'). Otherwise returns c unchanged.
 *
 * @param c Character to convert.
 * @return Lower-case equivalent of c, or c unchanged if no conversion applies.
 */
char ft_tolower(char c);

/**
 * @brief Convert a lower-case letter to the corresponding upper-case.
 *
 * If c is a lower-case ASCII letter ('a'..'z'), returns the corresponding
 * upper-case letter ('A'..'Z'). Otherwise returns c unchanged.
 *
 * @param c Character to convert.
 * @return Upper-case equivalent of c, or c unchanged if no conversion applies.
 */
char ft_toupper(char c);
