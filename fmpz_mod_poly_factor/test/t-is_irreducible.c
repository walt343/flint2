/*
    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2012 Lina Kulakova

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz_vec.h"
#include "fmpz_mod_poly.h"
#include "ulong_extras.h"

int
main(void)
{
    int iter;
    FLINT_TEST_INIT(state);
    

    flint_printf("is_irreducible....");
    fflush(stdout);

    for (iter = 0; iter < 10 * flint_test_multiplier(); iter++)
    {
        fmpz_mod_poly_t poly1, poly2;
        fmpz_t modulus;
        slong length;
        int i, num;

        fmpz_init_set_ui(modulus, n_randtest_prime(state, 0));

        fmpz_mod_poly_init(poly1, modulus);
        fmpz_mod_poly_init(poly2, modulus);

        length = n_randint(state, 10) + 2;
        do
        {
            fmpz_mod_poly_randtest(poly1, state, length);
            if (!fmpz_mod_poly_is_zero(poly1))
                fmpz_mod_poly_make_monic(poly1, poly1);
        }
        while ((!fmpz_mod_poly_is_irreducible(poly1)) || (poly1->length < 2));

        num = n_randint(state, 5) + 1;

        for (i = 0; i < num; i++)
        {
            do
            {
                fmpz_mod_poly_randtest(poly2, state, length);
                if (!fmpz_mod_poly_is_zero(poly1))
                    fmpz_mod_poly_make_monic(poly2, poly2);
            }
            while ((!fmpz_mod_poly_is_irreducible(poly2)) || (poly2->length < 2));

            fmpz_mod_poly_mul(poly1, poly1, poly2);
        }

        if (fmpz_mod_poly_is_irreducible(poly1))
        {
            flint_printf("Error: reducible polynomial declared irreducible!\n");
            flint_printf("poly:\n");
            fmpz_mod_poly_print(poly1);
            flint_printf("\n");
            abort();
        }

        fmpz_clear(modulus);
        fmpz_mod_poly_clear(poly1);
        fmpz_mod_poly_clear(poly2);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
