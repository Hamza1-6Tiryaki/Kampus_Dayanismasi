// src/asm_modulleri.cpp
// Amac: x86 satir ici Assembly (_asm) ile 32-bit veri paketi kodlama ve cozme modulleri
// Paket Duzeni: [Kategori: 4-bit (31..28)] [Aciliyet: 4-bit (27..24)] [Bina: 8-bit (23..16)] [Donem: 8-bit (15..8)] [Bayrak: 8-bit (7..0)]

#include "paket.h"

// 32-bit Paket Kodlayici (x86 Assembly Surumu)
// Her alan once AND ile maskelenir (tasma korumasi), SHL ile bit konumuna kaydirilir ve OR ile EAX'te birlestirilir.
unsigned KampusVeriKodla_ASM(unsigned kat, unsigned acil, unsigned bina, unsigned donem, unsigned bayrak) {
    unsigned paket = 0;
    _asm {
        XOR EAX, EAX        // EAX yazmacini sifirla (32-bit sonuc paketi EAX icinde birlestirilecek)

        // 1. Kategori Alani (Bit 31..28 - 4 bit)
        MOV ECX, kat        // Kategori parametresini gecici ECX yazmacina yukle
        AND ECX, 0x0F       // Tasma korumasi: Sadece alt 4 biti (0-15) koru, ust bitleri sifirla
        SHL ECX, 28         // Kategoriyi en yuksek anlamli 4 bit konumuna (Bit 31-28) sola kaydir
        OR  EAX, ECX        // Kaydirilan kategori bitlerini ana pakete (EAX) OR kapisi ile yerlestir

        // 2. Aciliyet Alani (Bit 27..24 - 4 bit)
        MOV ECX, acil       // Aciliyet parametresini ECX yazmacina yukle
        AND ECX, 0x0F       // Tasma korumasi: Sadece alt 4 biti (0-15) koru
        SHL ECX, 24         // Aciliyeti Bit 27-24 konumuna sola kaydir
        OR  EAX, ECX        // Aciliyet bitlerini ana pakete (EAX) OR ile ekle

        // 3. Bina Kodu Alani (Bit 23..16 - 8 bit)
        MOV ECX, bina       // Bina kodu parametresini ECX yazmacina yukle
        AND ECX, 0xFF       // Tasma korumasi: Sadece alt 8 biti (0-255) koru
        SHL ECX, 16         // Bina kodunu Bit 23-16 konumuna (3. bayt) sola kaydir
        OR  EAX, ECX        // Bina kodu bitlerini ana pakete (EAX) OR ile ekle

        // 4. Donem Alani (Bit 15..8 - 8 bit)
        MOV ECX, donem      // Donem parametresini ECX yazmacina yukle
        AND ECX, 0xFF       // Tasma korumasi: Sadece alt 8 biti (0-255) koru
        SHL ECX, 8          // Donem bilgisini Bit 15-8 konumuna (2. bayt) sola kaydir
        OR  EAX, ECX        // Donem bitlerini ana pakete (EAX) OR ile ekle

        // 5. Bayrak Alani (Bit 7..0 - 8 bit)
        MOV ECX, bayrak     // Bayrak parametresini ECX yazmacina yukle
        AND ECX, 0xFF       // Tasma korumasi: Sadece alt 8 biti (Bit 7-0) koru (en alt baytta oldugu icin kaydirilmaz)
        OR  EAX, ECX        // Bayrak bitlerini ana paketin en alt baytina (EAX) OR ile ekle

        MOV paket, EAX      // Birlestirilen 32-bit paketi C++ yerel degiskenine aktar
    }
    return paket;
}

// 1. Kategori Cozucu (Bit 31..28 -> 4 bit)
unsigned Kategori_ASM(unsigned p) {
    unsigned sonuc = 0;
    _asm {
        MOV EAX, p          // 32-bit paketi EAX yazmacina yukle
        SHR EAX, 28         // Bit 31-28 arasindaki kategori alanini 28 bit saga kaydirarak Bit 3-0'a getir
        AND EAX, 0x0F       // Sadece alt 4 biti maskeleyerek kategori degerini (0-15) izole et
        MOV sonuc, EAX      // Cozulen kategori degerini C++ sonuc degiskenine aktar
    }
    return sonuc;
}

// 2. Aciliyet Cozucu (Bit 27..24 -> 4 bit)
unsigned Aciliyet_ASM(unsigned p) {
    unsigned sonuc = 0;
    _asm {
        MOV EAX, p          // 32-bit paketi EAX yazmacina yukle
        SHR EAX, 24         // Bit 27-24 arasindaki aciliyet alanini 24 bit saga kaydirarak Bit 3-0'a getir
        AND EAX, 0x0F       // Ustte kalan kategori bitlerini temizlemek icin alt 4 biti (0x0F) maskele
        MOV sonuc, EAX      // Cozulen aciliyet degerini C++ sonuc degiskenine aktar
    }
    return sonuc;
}

// 3. Bina Kodu Cozucu (Bit 23..16 -> 8 bit)
unsigned Bina_ASM(unsigned p) {
    unsigned sonuc = 0;
    _asm {
        MOV EAX, p          // 32-bit paketi EAX yazmacina yukle
        SHR EAX, 16         // Bit 23-16 arasindaki bina kodunu 16 bit saga kaydirarak en alt bayta (Bit 7-0) getir
        AND EAX, 0xFF       // Ustteki kategori ve aciliyet bitlerini temizlemek icin alt 8 biti (0xFF) maskele
        MOV sonuc, EAX      // Cozulen bina kodunu C++ sonuc degiskenine aktar
    }
    return sonuc;
}

// 4. Donem Cozucu (Bit 15..8 -> 8 bit)
unsigned Donem_ASM(unsigned p) {
    unsigned sonuc = 0;
    _asm {
        MOV EAX, p          // 32-bit paketi EAX yazmacina yukle
        SHR EAX, 8          // Bit 15-8 arasindaki donem alanini 8 bit saga kaydirarak en alt bayta (Bit 7-0) getir
        AND EAX, 0xFF       // Ustteki alanlari temizlemek icin sadece alt 8 biti (0xFF) maskele
        MOV sonuc, EAX      // Cozulen donem bilgisini C++ sonuc degiskenine aktar
    }
    return sonuc;
}

// 5. Bayrak Cozucu (Bit 7..0 -> 8 bit)
unsigned Bayrak_ASM(unsigned p) {
    unsigned sonuc = 0;
    _asm {
        MOV EAX, p          // 32-bit paketi EAX yazmacina yukle
        AND EAX, 0xFF       // Bayraklar zaten Bit 7-0'da oldugu icin kaydirmadan dogrudan alt 8 biti (0xFF) maskele
        MOV sonuc, EAX      // Cozulen 8-bit bayrak alanini C++ sonuc degiskenine aktar
    }
    return sonuc;
}

// 6. Sadelesmis Boole Eslestirme Karar Modulu (x86 Assembly Surumu)
// Sadelesmis Ifade: F = B . (A + (C . D'))
// Bit Sirasi: Bit 0 (1) = A (Bolge), Bit 1 (2) = B (Yetkinlik), Bit 2 (4) = C (Bos saat), Bit 3 (8) = D (Sinavi var)
int EslesmeUygunMu_ASM(unsigned int paket) {
    int sonuc = 0;          // Varsayilan karar: 0 (Uygun degil)
    _asm {
        MOV  EAX, paket     // 32-bit veri paketini EAX yazmacina yukle
        AND  EAX, 0xFF      // Sadece alt 8 bitlik bayrak alanini (Bit 7-0) birak, ust alanlari sifirla

        TEST EAX, 2         // Bit 1 (B = 2, Yetkinlik) kontrolu: B & 2 islemi yap (EAX degismez, ZF guncellenir)
        JZ   BITTI          // ZF=1 (B=0) ise yetkinlik yoktur; F = B.(...) ifadesi 0 olacagi icin BITTI'ye atla

        TEST EAX, 1         // Bit 0 (A = 1, Ayni bolge) kontrolu: B=1 iken A=1 ise diger sartlara bakmaya gerek yok
        JNZ  UYGUN          // ZF=0 (A=1) ise B.A = 1 saglandi; kisa devre ile dogrudan UYGUN etiketine atla

        TEST EAX, 4         // Bit 2 (C = 4, Bos saat uyumu) kontrolu: A=0 oldugu icin (C . D') terimi 1 olmali
        JZ   BITTI          // ZF=1 (C=0) ise bos saat uyumu yoktur; eslesme saglanamaz, BITTI'ye atla

        TEST EAX, 8         // Bit 3 (D = 8, Destekcinin o gun sinavi var) kontrolu: D' = 1 olmasi icin D = 0 olmali
        JNZ  BITTI          // ZF=0 (D=1, yani sinavi var) ise D'=0 olur; eslesme saglanamaz, BITTI'ye atla

    UYGUN:                  // Eslesme kosullari (B=1 ve (A=1 veya (C=1 ve D=0))) basariyla saglandi
        MOV  sonuc, 1       // Sonuc degiskenine 1 (Eslesme uygun) degerini ata

    BITTI:                  // Cikis noktasi: Kosullar saglanmadiysa sonuc baslangictaki 0 degerini korur
    }
    return sonuc;
}

