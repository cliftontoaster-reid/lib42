/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:22:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/memory/ops.h"

static void* expect_memrchr(const void* s, int c, size_t n) {
  const unsigned char* p = (const unsigned char*)s;
  for (size_t i = 0; i < n; ++i) {
    /* noop */
  }
  for (size_t i = n; i-- > 0;) {
    if (p[i] == (unsigned char)c) return (void*)(p + i);
  }
  return NULL;
}

Test(ft_memrchr, last_occurrence_at_end) {
  unsigned char buf[] = {1, 2, 3, 4};
  void* p = ft_memrchr(buf, 4, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 3);
}

Test(ft_memrchr, last_occurrence_in_middle) {
  unsigned char buf[] = {5, 6, 7, 6, 5};
  void* p = ft_memrchr(buf, 6, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 3);
}

Test(ft_memrchr, last_occurrence_at_beginning) {
  unsigned char buf[] = {9, 1, 2, 3};
  void* p = ft_memrchr(buf, 9, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 0);
}

Test(ft_memrchr, multiple_occurrences_returns_last) {
  unsigned char buf[] = {2, 3, 2, 3, 2};
  void* p = ft_memrchr(buf, 3, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 3);
}

Test(ft_memrchr, not_found_null) {
  unsigned char buf[] = {1, 1, 1};
  void* p = ft_memrchr(buf, 5, sizeof(buf));
  cr_assert_null(p);
}

Test(ft_memrchr, search_for_null_byte) {
  unsigned char buf[] = {1, 0, 2, 0};
  void* p = ft_memrchr(buf, 0, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 3);
}

Test(ft_memrchr, zero_length_search) {
  unsigned char buf[] = {1, 2, 3};
  void* p = ft_memrchr(buf, 1, 0);
  cr_assert_null(p);
}

Test(ft_memrchr, high_byte_search) {
  unsigned char buf[] = {0xFF, 0x01, 0xFF};
  void* p = ft_memrchr(buf, 0xFF, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 2);
}

Test(ft_memrchr, binary_random_buffer) {
  unsigned char buf[50];
  for (size_t i = 0; i < sizeof(buf); ++i) buf[i] = (unsigned char)(i * 11 + 5);
  unsigned char target = buf[10];
  void* p = ft_memrchr(buf, target, sizeof(buf));
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 10);
}

Test(ft_memrchr, partial_range_excludes_later_occurrence) {
  unsigned char buf[] = {1, 2, 3, 4, 3};
  void* p = ft_memrchr(buf, 3, 4);  // search only first 4 bytes
  cr_assert_not_null(p);
  cr_assert_eq((unsigned char*)p - buf, 2);
}
