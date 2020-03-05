#include <iostream>
using namespace std;

class Base
{
public:
    Base() {}
    int normal_function(int a)
    {
        return a;
    }
    int Base_doesnot_implement_this_one() const = delete;
};

class Derived : public Base
{
public:
    Derived(){}

    // Overriding
    int normal_function(int a)
    {
        return a * 2;
    }

    int call_base_normal_function(int a)
    {
        return Base::normal_function(a);
    }

    int Base_doesnot_implement_this_one() const
    {
        return 153;
    }
};


int main()
{
    Base b;
    Derived d;

    cout << "Calling Base::normal_function(33)" << b.normal_function(33) << endl;
    // cout << "Calling Base::Base_doesnot_implement_this_one()" << b.Base_doesnot_implement_this_one() << endl; -> error, this is expected as function is deleted
    cout << "Calling Derived::normal_function(33)" << d.normal_function(33) << endl;
    cout << "Calling Derived::call_base_normal_function(33)" << d.call_base_normal_function(33) << endl;
    cout << "Calling Derived::Base_doesnot_implement_this_one(33)" << d.Base_doesnot_implement_this_one() << endl;

    return 0;
}


// Resulting generated ELF : Base::Base_doesnot_implement_this_one has effectively not been generated ! No symbols exist for that
/*
En-tête ELF:
  Magique:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Classe:                            ELF64
  Données:                          complément à 2, système à octets de poids faible d'abord (little endian)
  Version:                           1 (actuelle)
  OS/ABI:                            UNIX - System V
  Version ABI:                       0
  Type:                              DYN (fichier objet partagé)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Adresse du point d'entrée:               0x1100
  Début des en-têtes de programme :          64 (octets dans le fichier)
  Début des en-têtes de section :          15832 (octets dans le fichier)
  Fanions:                           0x0
  Taille de cet en-tête:             64 (octets)
  Taille de l'en-tête du programme:  56 (octets)
  Nombre d'en-tête du programme:     13
  Taille des en-têtes de section:    64 (octets)
  Nombre d'en-têtes de section:      31
  Table d'index des chaînes d'en-tête de section: 30

En-têtes de section :
  [Nr] Nom               Type             Adresse           Décalage
       Taille            TaillEntrée      Fanion Lien  Info  Alignement
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000318  00000318
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.gnu.propert NOTE             0000000000000338  00000338
       0000000000000020  0000000000000000   A       0     0     8
  [ 3] .note.gnu.build-i NOTE             0000000000000358  00000358
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .note.ABI-tag     NOTE             000000000000037c  0000037c
       0000000000000020  0000000000000000   A       0     0     4
  [ 5] .gnu.hash         GNU_HASH         00000000000003a0  000003a0
       0000000000000028  0000000000000000   A       6     0     8
  [ 6] .dynsym           DYNSYM           00000000000003c8  000003c8
       0000000000000168  0000000000000018   A       7     1     8
  [ 7] .dynstr           STRTAB           0000000000000530  00000530
       0000000000000188  0000000000000000   A       0     0     1
  [ 8] .gnu.version      VERSYM           00000000000006b8  000006b8
       000000000000001e  0000000000000002   A       6     0     2
  [ 9] .gnu.version_r    VERNEED          00000000000006d8  000006d8
       0000000000000050  0000000000000000   A       7     2     8
  [10] .rela.dyn         RELA             0000000000000728  00000728
       0000000000000120  0000000000000018   A       6     0     8
  [11] .rela.plt         RELA             0000000000000848  00000848
       0000000000000090  0000000000000018  AI       6    24     8
  [12] .init             PROGBITS         0000000000001000  00001000
       000000000000001b  0000000000000000  AX       0     0     4
  [13] .plt              PROGBITS         0000000000001020  00001020
       0000000000000070  0000000000000010  AX       0     0     16
  [14] .plt.got          PROGBITS         0000000000001090  00001090
       0000000000000010  0000000000000010  AX       0     0     16
  [15] .plt.sec          PROGBITS         00000000000010a0  000010a0
/Base
… escamotage
    56: 00000000000013b6    15 FUNC    WEAK   DEFAULT   16 _ZN4BaseC1Ev
    57: 0000000000004008     0 OBJECT  GLOBAL HIDDEN    25 __dso_handle
    58: 00000000000013da    31 FUNC    WEAK   DEFAULT   16 _ZN7DerivedC1Ev
    59: 00000000000014c8     0 FUNC    GLOBAL HIDDEN    17 _fini
    60: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __cxa_atexit@@GLIBC_2.2.5
    61: 0000000000001100    47 FUNC    GLOBAL DEFAULT   16 _start
    62: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZStlsISt11char_traitsIcE
    63: 00000000000013b6    15 FUNC    WEAK   DEFAULT   16 _ZN4BaseC2Ev
    64: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSolsEPFRSoS_E@@GLIBCXX
    65: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __stack_chk_fail@@GLIBC_2
    66: 0000000000004010     0 OBJECT  GLOBAL HIDDEN    25 __TMC_END__
    67: 0000000000001410    38 FUNC    WEAK   DEFAULT   16 _ZN7Derived25call_base_no
    68: 0000000000004020   272 OBJECT  GLOBAL DEFAULT   26 _ZSt4cout@@GLIBCXX_3.4
    69: 00000000000013da    31 FUNC    WEAK   DEFAULT   16 _ZN7DerivedC2Ev
    70: 0000000000004000     0 NOTYPE  GLOBAL DEFAULT   25 __data_start
    71: 0000000000004138     0 NOTYPE  GLOBAL DEFAULT   26 _end
    72: 0000000000004010     0 NOTYPE  GLOBAL DEFAULT   26 __bss_start
    73: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSt8ios_base4InitC1Ev@@
    74: 0000000000001450   101 FUNC    GLOBAL DEFAULT   16 __libc_csu_init
    75: 00000000000013c6    20 FUNC    WEAK   DEFAULT   16 _ZN4Base15normal_function
    76: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSolsEi@@GLIBCXX_3.4
    77: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
    78: 00000000000014c0     5 FUNC    GLOBAL DEFAULT   16 __libc_csu_fini
    79: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_
    80: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    81: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
    82: 00000000000013fa    22 FUNC    WEAK   DEFAULT   16 _ZN7Derived15normal_funct
    83: 0000000000001436    19 FUNC    WEAK   DEFAULT   16 _ZNK7Derived31Base_doesno
    84: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _ZNSt8ios_base4InitD1Ev@@

Histogram for `.gnu.hash' bucket list length (total of 2 buckets):
 Long.   Nombre     % de couverture totale
      0  1          ( 50.0%)
      1  0          (  0.0%)      0.0%
      2  1          ( 50.0%)    100.0%

La section des symboles de version « .gnu.version » contient 15 entrées :
 Adr: 0x00000000000006b8  Décalage: 0x0006b8  Lien: 6 (.dynsym)
  000:   0 (*local*)       3 (GLIBCXX_3.4)   2 (GLIBC_2.2.5)   3 (GLIBCXX_3.4)
  004:   3 (GLIBCXX_3.4)   4 (GLIBC_2.4)     3 (GLIBCXX_3.4)   3 (GLIBCXX_3.4)
  008:   0 (*local*)       2 (GLIBC_2.2.5)   0 (*local*)       0 (*local*)
  00c:   3 (GLIBCXX_3.4)   2 (GLIBC_2.2.5)   3 (GLIBCXX_3.4)

La section de dépendances de version « .gnu.version_r » contient 2 entrées :
 Adr: 0x00000000000006d8  Décalage: 0x0006d8  Lien: 7 (.dynstr)
  000000: Version: 1  Fichier: libstdc++.so.6  Compteur: 1
  0x0010:   Nom: GLIBCXX_3.4  Fanions: aucun  Version: 3
  0x0020: Version: 1  Fichier: libc.so.6  Compteur: 2
  0x0030:   Nom: GLIBC_2.4  Fanions: aucun  Version: 4
  0x0040:   Nom: GLIBC_2.2.5  Fanions: aucun  Version: 2

Affichage des notes trouvées dans: .note.gnu.property
  Propriétaire        Taille des données	Description
  GNU                  0x00000010	NT_GNU_PROPERTY_TYPE_0
      Propriétés: x86 feature: IBT, SHSTK
*/