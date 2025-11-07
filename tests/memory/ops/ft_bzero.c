/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:46:05 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 09:50:37 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "memory/ops.h"

// -zero_standard_region
// -zero_length_no_change
// -zero_large_region
// -zero_already_zeroed
// -zero_partial_then_verify_rest
// -binary_data_zeroing
// -random_zero_ranges

Test(ft_bzero, zero_standard_region) {
  char buffer[10];
  memset(buffer, 'A', sizeof(buffer));
  ft_bzero(buffer, 10);
  for (size_t i = 0; i < sizeof(buffer); i++) {
    cr_assert_eq(buffer[i], 0);
  }
}

Test(ft_bzero, zero_length_no_change) {
  char buffer[10];
  memset(buffer, 'B', sizeof(buffer));
  ft_bzero(buffer, 0);
  for (size_t i = 0; i < sizeof(buffer); i++) {
    cr_assert_eq(buffer[i], 'B');
  }
}

Test(ft_bzero, zero_large_region) {
  size_t n = 1024 * 1024;  // 1 MiB
  char* buffer = malloc(n);
  cr_assert_not_null(buffer);
  memset(buffer, 'C', n);
  ft_bzero(buffer, n);
  for (size_t i = 0; i < n; i++) {
    cr_assert_eq(buffer[i], 0);
  }
  free(buffer);
}

Test(ft_bzero, zero_already_zeroed) {
  char buffer[20] = {0};
  ft_bzero(buffer, sizeof(buffer));
  for (size_t i = 0; i < sizeof(buffer); i++) {
    cr_assert_eq(buffer[i], 0);
  }
}

Test(ft_bzero, zero_partial_then_verify_rest) {
  char buffer[15];
  memset(buffer, 'D', sizeof(buffer));
  ft_bzero(buffer, 5);
  for (size_t i = 0; i < 5; i++) {
    cr_assert_eq(buffer[i], 0);
  }
  for (size_t i = 5; i < sizeof(buffer); i++) {
    cr_assert_eq(buffer[i], 'D');
  }
}

Test(ft_bzero, binary_data_zeroing) {
  unsigned char buffer[8] = {0xFF, 0xAB, 0x34, 0x78, 0x90, 0xCD, 0xEF, 0x12};
  ft_bzero(buffer, sizeof(buffer));
  for (size_t i = 0; i < sizeof(buffer); i++) {
    cr_assert_eq(buffer[i], 0);
  }
}

Test(ft_bzero, random_zero_ranges) {
  srand(42);
  for (int t = 0; t < 100; ++t) {
    size_t n = (rand() % 64) + 1;
    unsigned char buffer[64];
    for (size_t i = 0; i < sizeof(buffer); i++) {
      buffer[i] = (unsigned char)((rand() % 255) + 1);
    }
    size_t zero_len = rand() % (n + 1);
    ft_bzero(buffer, zero_len);
    for (size_t i = 0; i < zero_len; i++) {
      cr_assert_eq(buffer[i], 0);
    }
    for (size_t i = zero_len; i < n; i++) {
      cr_assert_neq(buffer[i], 0);
    }
  }
}
