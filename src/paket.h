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