#pragma once
// Amac: 32-bit veri paketi kodlama, cozme ve bayrak sabitleri

// Bayrak bayti (Bit 7 - Bit 0) bit maskesi sabitleri
const unsigned BAYRAK_A_BOLGE = 1u << 0; // Bit 0 (1)  : Ayni fakulte/bolge
const unsigned BAYRAK_B_YETKIN = 1u << 1; // Bit 1 (2)  : Ders/materyal yetkinligi
const unsigned BAYRAK_C_BOS_SAAT = 1u << 2; // Bit 2 (4)  : Bos saat uyumu
const unsigned BAYRAK_D_SINAVI_VAR = 1u << 3; // Bit 3 (8)  : Destekcinin o gun sinavi var
const unsigned BAYRAK_UST_DONEM = 1u << 4; // Bit 4 (16) : Ust donem ogrencisi
const unsigned BAYRAK_LAB_YETKI = 1u << 5; // Bit 5 (32) : Lab yetkisi
const unsigned BAYRAK_REFAKAT = 1u << 6; // Bit 6 (64) : Engelsiz refakat gerekli
// Bit 7 (128): Bos / Rezerve

// 32-bit Paket Kodlayici (C++ Referans Surumu)
// Her alan once AND ile maskelenir (tasma korumasi), sonra sola kaydirilir ve OR ile birlestirilir.
inline unsigned KodlaCpp(unsigned kat, unsigned acil, unsigned bina, unsigned donem, unsigned bayrak) {
    return ((kat & 0x0Fu) << 28) |
        ((acil & 0x0Fu) << 24) |
        ((bina & 0xFFu) << 16) |
        ((donem & 0xFFu) << 8) |
        (bayrak & 0xFFu);
}

// 32-bit Paket Cozuculer: Once ilgili alani en saga kaydir (>>), sonra maskele (&)
inline unsigned Kategori(unsigned p) { return (p >> 28) & 0x0Fu; }
inline unsigned Aciliyet(unsigned p) { return (p >> 24) & 0x0Fu; }
inline unsigned Bina(unsigned p) { return (p >> 16) & 0xFFu; }
inline unsigned Donem(unsigned p) { return (p >> 8) & 0xFFu; }
inline unsigned Bayrak(unsigned p) { return p & 0xFFu; }