// test/test_boole.cpp
// Amac: 4 degiskenli (A, B, C, D) 16 satirlik Boole dogruluk tablosu ve FHam == FCpp esdegerlik testi

#include <cstdio>
#include <cassert>
#include "../src/paket.h"

void BooleTestleriniCalistir() {
    printf("\n+----+---+---+---+---+------+------+\n");
    printf("| #  | A | B | C | D | FHam | FCpp |\n");
    printf("+----+---+---+---+---+------+------+\n");

    for (unsigned i = 0; i < 16; ++i) {
        // Sprint 0 bayrak bit sirasina birebir uyumlu:
        // Bit 0 (1): A (Ayni bolge), Bit 1 (2): B (Yetkinlik), Bit 2 (4): C (Bos saat), Bit 3 (8): D (Sinavi var)
        bool A = (i & 1u) != 0;
        bool B = (i & 2u) != 0;
        bool C = (i & 4u) != 0;
        bool D = (i & 8u) != 0;

        bool fHam = FHam(A, B, C, D);
        bool fCpp = FCpp(A, B, C, D);

        printf("| %2u | %d | %d | %d | %d |  %d   |  %d   |\n",
            i, A ? 1 : 0, B ? 1 : 0, C ? 1 : 0, D ? 1 : 0, fHam ? 1 : 0, fCpp ? 1 : 0);

        // Her kombinasyonda ham ve sadelesmis ifadelerin esdegerligini dogrula
        assert(fHam == fCpp);
    }

    printf("+----+---+---+---+---+------+------+\n");
    printf("[BASARILI] Gorev 2.1: 16 satirlik Boole dogruluk tablosunda FHam ve FCpp birebir eslesti!\n");
}
