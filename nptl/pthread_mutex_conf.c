/* Pthread mutex tunable parameters.
   Copyright (C) 2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if HAVE_TUNABLES
# define TUNABLE_NAMESPACE pthread
#include <pthread_mutex_conf.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>  /* Get STDOUT_FILENO for _dl_printf.  */
#include <elf/dl-tunables.h>

struct mutex_config __mutex_aconf =
{
  /* The maximum number of times a thread should spin on the lock before
  calling into kernel to block.  */
  .spin_count = DEFAULT_ADAPTIVE_COUNT,
};

static void
TUNABLE_CALLBACK (set_mutex_spin_count) (tunable_val_t *valp)
{
  __mutex_aconf.spin_count = (int32_t) (valp)->numval;
}

void
__pthread_tunables_init (void)
{
  TUNABLE_GET (mutex_spin_count, int32_t,
               TUNABLE_CALLBACK (set_mutex_spin_count));
}
#endif
