/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:05:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/memory/ops.h"

Test(ft_memcmp, equal_buffers_returns_zero) {
  unsigned char a[] = {1, 2, 3, 4, 5};
  unsigned char b[] = {1, 2, 3, 4, 5};
  cr_assert_eq(ft_memcmp(a, b, sizeof(a)), 0);
}

Test(ft_memcmp, diff_first_byte) {
  unsigned char a[] = {0, 2, 3};
  unsigned char b[] = {1, 2, 3};
  cr_assert_lt(ft_memcmp(a, b, 3), 0);
}

Test(ft_memcmp, diff_middle_byte) {
  unsigned char a[] = {1, 2, 0, 4};
  unsigned char b[] = {1, 2, 5, 4};
  cr_assert_lt(ft_memcmp(a, b, 4), 0);
}

Test(ft_memcmp, diff_last_byte) {
  unsigned char a[] = {1, 2, 3, 7};
  unsigned char b[] = {1, 2, 3, 8};
  cr_assert_lt(ft_memcmp(a, b, 4), 0);
}

Test(ft_memcmp, zero_length_compare) {
  unsigned char a[] = {9, 9};
  unsigned char b[] = {1, 2};
  cr_assert_eq(ft_memcmp(a, b, 0), 0);
}

Test(ft_memcmp, partial_compare_ignores_later_diff) {
  unsigned char a[] = {1, 2, 3, 4, 5};
  unsigned char b[] = {1, 2, 3, 4, 9};
  cr_assert_eq(ft_memcmp(a, b, 4), 0);
}

Test(ft_memcmp, signed_vs_unsigned_ordering) {
  unsigned char a[] = {0x80};
  unsigned char b[] = {0x7F};
  /* unsigned comparison: 0x80 > 0x7F */
  cr_assert_gt(ft_memcmp(a, b, 1), 0);
}

Test(ft_memcmp, high_byte_vs_low_byte) {
  unsigned char a[] = {0xFF, 0x00};
  unsigned char b[] = {0x00, 0xFF};
  cr_assert_gt(ft_memcmp(a, b, 1), 0);
}

Test(ft_memcmp, large_equal_then_diff) {
  size_t n = 1024;
  unsigned char* a = malloc(n);
  unsigned char* b = malloc(n);
  cr_assert_not_null(a);
  cr_assert_not_null(b);
  memset(a, 0xAA, n);
  memset(b, 0xAA, n);
  b[n - 1] = 0xAB;
  cr_assert_lt(ft_memcmp(a, b, n), 0);
  free(a);
  free(b);
}

Test(ft_memcmp, random_pairs_consistency) {
  srand(7);  // NOLINT(cert-msc51-cpp)
  for (int t = 0; t < 200; ++t) {
    size_t n = rand() % 128;  // NOLINT(cert-msc50-cpp)
    unsigned char* a = malloc(n ? n : 1);
    unsigned char* b = malloc(n ? n : 1);
    cr_assert_not_null(a);
    cr_assert_not_null(b);
    for (size_t i = 0; i < n; ++i) {
      a[i] = rand();  // NOLINT(cert-msc50-cpp)
      b[i] = rand();  // NOLINT(cert-msc50-cpp)
    }
    int r1 = ft_memcmp(a, b, n);
    int r2 = memcmp(a, b, n);
    /* normalize sign only: memcmp and ft_memcmp may differ in magnitude */
    cr_assert_eq((r1 > 0) - (r1 < 0), (r2 > 0) - (r2 < 0));
    free(a);
    free(b);
  }
}
