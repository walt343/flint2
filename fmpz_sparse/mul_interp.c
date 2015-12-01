/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
     
    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Authored 2015 by A. Whitman Groves; US Government work in the public domain. 

******************************************************************************/

#include "fmpz_sparse.h"
#include "fmpz_vec.h"

void 
fmpz_sparse_mul_interp(fmpz_sparse_t res, flint_rand_t state, const fmpz_sparse_t poly1, 
    const fmpz_sparse_t poly2, slong terms)
{
  fmpz_sparse_bp_interp_t f;
  fmpz_t h, d;

  fmpz_init(h);
  fmpz_init(d);

  fmpz_sparse_height(h, poly1);
  fmpz_add(d, poly1->expons, poly2->expons);

  fmpz_sparse_bp_interp_init(f, terms, h, d, state);
  fmpz_sparse_bp_interp_eval(f, poly1);

  fmpz_sparse_bp_interp_mul(f, poly2);

  fmpz_sparse_bp_interp_interp(res, f);

  fmpz_sparse_bp_interp_clear(f);

  fmpz_clear(h);
  fmpz_clear(d);
}
