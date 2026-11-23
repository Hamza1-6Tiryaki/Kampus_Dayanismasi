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

void AsmKarsilastirmaTesti() {
    unsigned toplamTest = 0;

    for (unsigned kat = 0; kat <= 15; ++kat) {
        for (unsigned acil = 0; acil <= 15; ++acil) {
            for (unsigned bina = 0; bina <= 255; bina += 17) {
                // Farkli donem ve bayrak kombinasyonlari uret (0..255 araliginda)
                unsigned donem = (kat * 17 + acil * 13 + bina) & 0xFFu;
                unsigned bayrak = ((kat << 4) ^ (acil * 15) ^ bina) & 0xFFu;

                unsigned pCpp = KodlaCpp(kat, acil, bina, donem, bayrak);
                unsigned pAsm = KampusVeriKodla_ASM(kat, acil, bina, donem, bayrak);

                if (pCpp != pAsm) {
                    printf("FARK! kat=%u acil=%u bina=%u donem=%u bayrak=%u -> Cpp=0x%08X, ASM=0x%08X\n",
                        kat, acil, bina, donem, bayrak, pCpp, pAsm);
                    assert(pCpp == pAsm);
                }

                // ASM cozucu fonksiyonlarla gidis-donus (round-trip) dogrulamasi
                assert(Kategori_ASM(pAsm) == kat);
                assert(Aciliyet_ASM(pAsm) == acil);
                assert(Bina_ASM(pAsm) == bina);
                assert(Donem_ASM(pAsm) == donem);
                assert(Bayrak_ASM(pAsm) == bayrak);

                ++toplamTest;
            }
        }
    }

    // Ek tasma (overflow) kontrolu: C++ ve ASM ayni maskelemeyi yapmali
    unsigned pTasmaCpp = KodlaCpp(20, 31, 300, 511, 0x1FF);
    unsigned pTasmaAsm = KampusVeriKodla_ASM(20, 31, 300, 511, 0x1FF);
    if (pTasmaCpp != pTasmaAsm) {
        printf("FARK (Tasma Testi)! Cpp=0x%08X, ASM=0x%08X\n", pTasmaCpp, pTasmaAsm);
        assert(pTasmaCpp == pTasmaAsm);
    }
    assert(Kategori_ASM(pTasmaAsm) == 4u);
    assert(Aciliyet_ASM(pTasmaAsm) == 15u);
    assert(Bina_ASM(pTasmaAsm) == (300u & 0xFFu));
    assert(Donem_ASM(pTasmaAsm) == 255u);
    assert(Bayrak_ASM(pTasmaAsm) == 0xFFu);

    printf("[BASARILI] Gorev 1.2: %u kombinasyon icin C++ ve x86 ASM kodlayici/cozucu birebir eslesti!\n", toplamTest);
}
