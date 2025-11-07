/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:35:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:35:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "memory/ops.h"

static void* expect_memmem(const void* haystack, size_t hlen,
                           const void* needle, size_t nlen) {
  if (nlen == 0) return (void*)haystack;
  if (nlen > hlen) return NULL;
  const unsigned char* h = (const unsigned char*)haystack;
  const unsigned char* n = (const unsigned char*)needle;
  for (size_t i = 0; i + nlen <= hlen; ++i) {
    if (memcmp(h + i, n, nlen) == 0) return (void*)(h + i);
  }
  return NULL;
}

Test(ft_memmem, needle_empty_returns_haystack) {
  unsigned char h[] = {1, 2, 3};
  unsigned char n[] = {};
  void* p = ft_memmem(h, sizeof(h), n, 0);
  cr_assert_eq(p, h);
}

Test(ft_memmem, needle_longer_than_haystack_null) {
  unsigned char h[] = {1, 2};
  unsigned char n[] = {1, 2, 3};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_null(p);
}

Test(ft_memmem, needle_at_beginning) {
  unsigned char h[] = {9, 8, 7, 6};
  unsigned char n[] = {9, 8};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_eq(p, h);
}

Test(ft_memmem, needle_in_middle) {
  unsigned char h[] = {0, 1, 2, 3, 4};
  unsigned char n[] = {2, 3};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_eq((unsigned char*)p - h, 2);
}

Test(ft_memmem, needle_at_end) {
  unsigned char h[] = {1, 2, 3, 4};
  unsigned char n[] = {3, 4};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_eq((unsigned char*)p - h, 2);
}

Test(ft_memmem, needle_repeating_pattern_first_match) {
  unsigned char h[] = {1, 1, 1, 1, 2};
  unsigned char n[] = {1, 1};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_eq((unsigned char*)p - h, 0);
}

Test(ft_memmem, needle_not_found) {
  unsigned char h[] = {1, 2, 3};
  unsigned char n[] = {4};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_null(p);
}

Test(ft_memmem, binary_with_nulls_match) {
  unsigned char h[] = {0, 1, 0, 2, 3};
  unsigned char n[] = {0, 2};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_eq((unsigned char*)p - h, 2);
}

Test(ft_memmem, single_byte_needle) {
  unsigned char h[] = {7, 8, 9};
  unsigned char n[] = {8};
  void* p = ft_memmem(h, sizeof(h), n, 1);
  cr_assert_eq((unsigned char*)p - h, 1);
}

Test(ft_memmem, whole_buffer_match) {
  unsigned char h[] = {1, 2, 3};
  unsigned char n[] = {1, 2, 3};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_eq(p, h);
}

Test(ft_memmem, overlap_near_end_no_overread) {
  unsigned char h[] = {1, 2, 3, 4};
  unsigned char n[] = {4, 5};
  void* p = ft_memmem(h, sizeof(h), n, sizeof(n));
  cr_assert_null(p);
}

Test(ft_memmem, multiple_matches_only_first) {
  unsigned char h[] = {1, 2, 1, 2, 1, 2};
  unsigned char n[] = {1, 2};
  void* p = ft_memmem(h, sizeof(h), n, 2);
  cr_assert_eq((unsigned char*)p - h, 0);
}

Test(ft_memmem, random_haystack_and_needle) {
  srand(13);  // NOLINT(cert-msc51-cpp)
  for (int t = 0; t < 200; ++t) {
    size_t hlen = (rand() % 128) + 1;  // NOLINT(cert-msc50-cpp)
    size_t nlen = (rand() % 16);       // NOLINT(cert-msc50-cpp)
    unsigned char* h = malloc(hlen);
    unsigned char* n = malloc(nlen ? nlen : 1);
    cr_assert_not_null(h);
    cr_assert_not_null(n);
    for (size_t i = 0; i < hlen; ++i)
      h[i] = rand() & 0xFF;  // NOLINT(cert-msc50-cpp)
    for (size_t i = 0; i < nlen; ++i)
      n[i] = rand() & 0xFF;  // NOLINT(cert-msc50-cpp)
    void* r1 = ft_memmem(h, hlen, n, nlen);
    void* r2 = expect_memmem(h, hlen, n, nlen);
    cr_assert_eq(r1, r2);
    free(h);
    free(n);
  }
}
