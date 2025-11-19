/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:48:16 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:55:16 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "42/ctype/ctype.h"

bool ft_islower(char c) {
  unsigned char uc = (unsigned char)c;
  return uc >= 'a' && uc <= 'z';
}
