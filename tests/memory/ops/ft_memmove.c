/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:33:39 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:04:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "memory/ops.h"

Test(ft_memmove, basic_forward_copy) {
  char src[] = "Hello World";
  char dest[12];
  void* ret = ft_memmove(dest, src, 12);
  cr_assert_eq(ret, dest);
  cr_assert_arr_eq(dest, src, 12);
}

Test(ft_memmove, basic_backward_copy) {
  char src[] = "Goodbye";
  char dest[8];
  void* ret = ft_memmove(dest, src, 8);
  cr_assert_eq(ret, dest);
  cr_assert_arr_eq(dest, src, 8);
}

Test(ft_memmove, overlap_src_before_dest) {
  char buffer[20] = "abcdefghij";
  char* dest = buffer + 2;
  char* src = buffer;
  ft_memmove(dest, src, 5);
  cr_assert_str_eq(buffer, "ababcdehij");
}

Test(ft_memmove, overlap_dest_before_src) {
  char buffer[20] = "abcdefghij";
  char* dest = buffer;
  char* src = buffer + 2;
  ft_memmove(dest, src, 5);
  cr_assert_str_eq(buffer, "cdefgfghij");
}

Test(ft_memmove, identical_pointers) {
  char buffer[] = "test";
  void* ret = ft_memmove(buffer, buffer, 5);
  cr_assert_eq(ret, buffer);
  cr_assert_str_eq(buffer, "test");
}

Test(ft_memmove, zero_length_move) {
  char buffer[] = "test";
  void* ret = ft_memmove(buffer, buffer + 1, 0);
  cr_assert_eq(ret, buffer);
  cr_assert_str_eq(buffer, "test");
}

Test(ft_memmove, move_with_null_bytes) {
  char src[10] = {'a', '\0', 'b', '\0', 'c', '\0', '\0', '\0', '\0', '\0'};
  char dest[10];
  void* ret = ft_memmove(dest, src, 10);
  cr_assert_eq(ret, dest);
  cr_assert_arr_eq(dest, src, 10);
}

Test(ft_memmove, large_overlapping_region) {
  char buffer[100] = {0};
  memset(buffer, 'x', 50);
  char* dest = buffer + 10;
  char* src = buffer;
  ft_memmove(dest, src, 40);
  for (int i = 0; i < 50; i++) cr_assert_eq(buffer[i], 'x');
  for (int i = 50; i < 100; i++) cr_assert_eq(buffer[i], 0);
}

Test(ft_memmove, partial_overlap_head) {
  char buffer[10] = "123456789";
  char* dest = buffer + 1;
  char* src = buffer;
  ft_memmove(dest, src, 3);
  cr_assert_str_eq(buffer, "112356789");
}

Test(ft_memmove, partial_overlap_tail) {
  char buffer[10] = "123456789";
  char* dest = buffer;
  char* src = buffer + 1;
  ft_memmove(dest, src, 3);
  cr_assert_str_eq(buffer, "234456789");
}

Test(ft_memmove, random_overlap_patterns) {
  char buffer[21] = "abcdefghijklmnopqrst";
  // Overlap with src starting 3 bytes before dest
  char* dest = buffer + 3;
  char* src = buffer;
  ft_memmove(dest, src, 7);
  cr_assert_str_eq(buffer, "abcabcdefgklmnopqrst");
  // Reset
  strcpy(buffer, "abcdefghijklmnopqrst");
  // Overlap with dest starting 3 bytes before src
  dest = buffer;
  src = buffer + 3;
  ft_memmove(dest, src, 7);
  cr_assert_str_eq(buffer, "defghijhijklmnopqrst");
}

Test(ft_memmove, return_value_is_dest) {
  char src[] = "test";
  char dest[5];
  cr_assert_eq(ft_memmove(dest, src, 5), dest);
}
