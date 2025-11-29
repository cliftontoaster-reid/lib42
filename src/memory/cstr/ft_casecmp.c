/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_casecmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:15:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/29 17:51:45 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42/memory/cstr.h"
#include "42/ctype/ctype.h"

int ft_casecmp(const char* s1, const char* s2) {
  size_t i = 0;
  while (s1[i] && s2[i]) {
    if (ft_tolower(s1[i]) != ft_tolower(s2[i])) {
      return ft_tolower(s1[i]) - ft_tolower(s2[i]);
    }
    i++;
  }
  return ft_tolower(s1[i]) - ft_tolower(s2[i]);
}
