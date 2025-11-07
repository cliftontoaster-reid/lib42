/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:46:22 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:55:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ctype/ctype.h"

bool ft_isascii(char c) {
  unsigned char uc = (unsigned char)c;
  return uc <= 127;
}
