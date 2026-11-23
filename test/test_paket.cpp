// test/test_paket.cpp
#include <cstdio>
#include <cassert>
#include "../src/paket.h"

void PaketTestleriniCalistir() {
    // 1. Sprint 0 Elle Ornek 1: kat=3, acil=12, bina=45, donem=6, bayrak=5 -> 0x3C2D0605
    unsigned p1 = KodlaCpp(3, 12, 45, 6, 5);
    assert(p1 == 0x3C2D0605u);

    // 2. Sprint 0 Elle Ornek 2: kat=1, acil=15, bina=200, donem=255, bayrak=0xFF -> 0x1FC8FFFF
    unsigned p2 = KodlaCpp(1, 15, 200, 255, 0xFF);
    assert(p2 == 0x1FC8FFFFu);

    // 3. Tasma (Overflow) Testi: kategori 4 bit (0-15) alir. 20 verilirse (20 & 0x0F = 4) olmali
    // ve yandaki aciliyet/bina alanlarina tasmamali.
    unsigned pTasma = KodlaCpp(20, 10, 100, 5, 3);
    assert(Kategori(pTasma) == 4u);
    assert(Aciliyet(pTasma) == 10u);

    // 4. Gidis-Donus (Round-Trip) Testi: Kodla -> Coz, orijinal degerler geri donmeli
    unsigned p3 = KodlaCpp(7, 9, 142, 12, BAYRAK_A_BOLGE | BAYRAK_B_YETKIN | BAYRAK_REFAKAT);
    assert(Kategori(p3) == 7u);
    assert(Aciliyet(p3) == 9u);
    assert(Bina(p3) == 142u);
    assert(Donem(p3) == 12u);
    assert(Bayrak(p3) == (BAYRAK_A_BOLGE | BAYRAK_B_YETKIN | BAYRAK_REFAKAT));

    printf("[BASARILI] Gorev 1.1: Tum C++ paket kodlayici ve cozucu testleri gecti!\n");
}