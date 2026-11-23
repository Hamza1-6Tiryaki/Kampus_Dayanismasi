#include <cstdio>

// Fonksiyonlarin test dosyalarinda oldugunu derleyiciye bildiriyoruz
void PaketTestleriniCalistir();
void AsmKarsilastirmaTesti();
void BooleTestleriniCalistir();
void BooleAsmTestleriniCalistir();
int main() {
    PaketTestleriniCalistir();
    AsmKarsilastirmaTesti();
    BooleTestleriniCalistir();
    BooleAsmTestleriniCalistir();
    return 0;
}