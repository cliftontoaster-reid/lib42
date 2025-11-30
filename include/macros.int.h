/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:58:59 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 10:47:48 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define FT_INT __attribute__((visibility("hidden")))

/* Deprecation helper: libraries can define LIB42_NO_DEPRECATED to suppress
 * deprecation attributes while building the library internals.
 */
#ifndef LIB42_NO_DEPRECATED
# define LIB42_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
# define LIB42_DEPRECATED(msg)
#endif