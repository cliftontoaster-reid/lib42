/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:20:48 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 12:31:05 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "42/memory/ops.h"

Test(ft_memcpy, basic_copy_small) {
  char src[] = "Hello, World!";
  char dest[20] = {0};

  ft_memcpy(dest, src, strlen(src) + 1);
  cr_assert_str_eq(dest, src);
}

Test(ft_memcpy, copy_entire_buffer) {
  char src[] = "Complete buffer copy test.";
  char dest[64];

  memset(dest, 0xAA, sizeof(dest));
  ft_memcpy(dest, src, sizeof(src));
  cr_assert_arr_eq(dest, src, sizeof(src));
}

Test(ft_memcpy, copy_with_null_bytes_inside) {
  unsigned char src[] = {0x01, 0x00, 0x02, 0x00, 0x03};
  unsigned char dest[5] = {0};

  ft_memcpy(dest, src, sizeof(src));
  cr_assert_arr_eq(dest, src, sizeof(src));
}

Test(ft_memcpy, zero_length_copy) {
  char src[] = "unchanged";
  char dest[] = "DEST";

  char* ret = ft_memcpy(dest, src, 0);
  cr_assert_eq(ret, dest);
  cr_assert_str_eq(dest, "DEST");
}

Test(ft_memcpy, return_value_is_dest) {
  char src[] = "abc";
  char dest[4] = {0};

  void* ret = ft_memcpy(dest, src, 4);
  cr_assert_eq(ret, dest);
}

Test(ft_memcpy, large_block_copy) {
  size_t n = 1024 * 1024;  // 1 MiB
  unsigned char* src = malloc(n);
  unsigned char* dest = malloc(n);

  cr_assert_not_null(src);
  cr_assert_not_null(dest);

  for (size_t i = 0; i < n; ++i) src[i] = (unsigned char)(i * 13);

  ft_memcpy(dest, src, n);
  cr_assert_arr_eq(dest, src, n);

  free(src);
  free(dest);
}

Test(ft_memcpy, non_aligned_addresses) {
  unsigned char* buf = malloc(64 + 3);
  cr_assert_not_null(buf);
  unsigned char* src = buf + 1;  // deliberately non-aligned
  unsigned char* dest = buf + 3;

  for (int i = 0; i < 60; ++i) src[i] = (unsigned char)(i + 1);

  ft_memcpy(dest, src, 60);
  cr_assert_arr_eq(dest, src, 60);

  free(buf);
}

Test(ft_memcpy, copy_preserves_source) {
  unsigned char src[] = {0xDE, 0xAD, 0xBE, 0xEF};
  unsigned char dest[4] = {0};

  unsigned char src_before[sizeof(src)];
  memcpy(src_before, src, sizeof(src));

  ft_memcpy(dest, src, sizeof(src));
  cr_assert_arr_eq(src, src_before, sizeof(src));
}

Test(ft_memcpy, copy_binary_data_high_bytes) {
  unsigned char src[] = {0x80, 0xFF, 0x7F, 0xAA};
  unsigned char dest[4] = {0};

  ft_memcpy(dest, src, sizeof(src));
  cr_assert_arr_eq(dest, src, sizeof(src));
}

Test(ft_memcpy, self_copy_pointer_equality) {
  unsigned char buf[] = {1, 2, 3, 4, 5};
  unsigned char before[sizeof(buf)];
  memcpy(before, buf, sizeof(buf));

  // copying from the same pointer should be a no-op and return the dest pointer
  void* ret = ft_memcpy(buf, buf, sizeof(buf));
  cr_assert_eq(ret, buf);
  cr_assert_arr_eq(buf, before, sizeof(buf));
}

Test(ft_memcpy, stress_many_small_copies) {
  srand(42);  // NOLINT(cert-msc51-cpp)
  for (int t = 0; t < 1000; ++t) {
    size_t n = (rand() % 32) + 1;  // NOLINT(cert-msc50-cpp)
    unsigned char src[64];
    unsigned char dest1[64];
    unsigned char dest2[64];

    for (size_t i = 0; i < n; ++i)
      src[i] = (unsigned char)rand();  // NOLINT(cert-msc50-cpp)

    memset(dest1, 0xEE, sizeof(dest1));
    memset(dest2, 0xEE, sizeof(dest2));

    ft_memcpy(dest1, src, n);
    memcpy(dest2, src, n);

    cr_assert_arr_eq(dest1, dest2, n);
  }
}

Test(ft_memcpy, random_buffers_consistency) {
  srand(123456);  // NOLINT(cert-msc51-cpp)
  for (int t = 0; t < 200; ++t) {
    size_t n = rand() % 512;  // NOLINT(cert-msc50-cpp)
    unsigned char* src = malloc(n ? n : 1);
    unsigned char* d1 = malloc(n ? n : 1);
    unsigned char* d2 = malloc(n ? n : 1);
    cr_assert_not_null(src);
    cr_assert_not_null(d1);
    cr_assert_not_null(d2);

    for (size_t i = 0; i < n; ++i)
      src[i] = (unsigned char)rand();  // NOLINT(cert-msc50-cpp)

    ft_memcpy(d1, src, n);
    memcpy(d2, src, n);

    cr_assert_arr_eq(d1, d2, n);

    free(src);
    free(d1);
    free(d2);
  }
}

// - basic_copy_small
// - copy_entire_buffer
// - copy_with_null_bytes_inside
// - zero_length_copy
// - return_value_is_dest
// - large_block_copy
// - non_aligned_addresses
// - copy_preserves_source
// - copy_binary_data_high_bytes
// - self_copy_pointer_equality (src == dest; document expectation / may skip)
// - stress_many_small_copies
// - random_buffers_consistency
