/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:00:00 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:02:19 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "42/alloc/vec.h"

void vec_free(t_vec* vec) {
  if (vec) {
    if (vec->data) free(vec->data);
    free(vec);
  }
}
