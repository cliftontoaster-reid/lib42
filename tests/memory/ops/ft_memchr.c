/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/memory/ops.h"

Test(ft_memchr, find_at_beginning) {
  unsigned char buf[] = {0x11, 0x22, 0x33};
  void* p = ft_memchr(buf, 0x11, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq(p, buf);
}

Test(ft_memchr, find_in_middle) {
  unsigned char buf[] = {0x00, 0xAA, 0xBB, 0xCC};
  void* p = ft_memchr(buf, 0xBB, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 2);
}

Test(ft_memchr, find_at_end) {
  unsigned char buf[] = {1, 2, 3, 4, 5};
  void* p = ft_memchr(buf, 5, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 4);
}

Test(ft_memchr, multiple_occurrences_first_only) {
  unsigned char buf[] = {0x7, 0x8, 0x7, 0x7};
  void* p = ft_memchr(buf, 0x7, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 0);
}

Test(ft_memchr, not_found_returns_null) {
  unsigned char buf[] = {0x1, 0x2, 0x3};
  void* p = ft_memchr(buf, 0xFF, sizeof(buf));
  cr_assert_null(p);
}

Test(ft_memchr, search_for_null_byte) {
  unsigned char buf[] = {'a', 0, 'b'};
  void* p = ft_memchr(buf, 0, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 1);
}

Test(ft_memchr, zero_length_search) {
  unsigned char buf[] = {1, 2, 3};
  void* p = ft_memchr(buf, 1, 0);
  cr_assert_null(p);
}

Test(ft_memchr, high_byte_search_0xFF) {
  unsigned char buf[] = {0x00, 0xFF, 0x10};
  void* p = ft_memchr(buf, 0xFF, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 1);
}

Test(ft_memchr, binary_haystack_random) {
  unsigned char buf[64];
  for (size_t i = 0; i < sizeof(buf); ++i) buf[i] = (unsigned char)(i * 7 + 3);
  unsigned char target = buf[20];
  void* p = ft_memchr(buf, target, 64);
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 20);
}

Test(ft_memchr, partial_range_excludes_later_match) {
  unsigned char buf[] = {1, 2, 3, 4, 5, 3};
  void* p = ft_memchr(buf, 3, 4);  // only search first 4 bytes
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 2);
}
