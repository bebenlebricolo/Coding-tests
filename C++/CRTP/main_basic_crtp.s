.LC0:
        .string "Hello from Derived 1 "
Derived1::say_hello_from_child() [clone .isra.0]:
        sub     rsp, 8
        mov     edi, OFFSET FLAT:_ZSt4cout
        mov     edx, 21
        mov     esi, OFFSET FLAT:.LC0
        call    std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)
        mov     edi, OFFSET FLAT:_ZSt4cout
        add     rsp, 8
        jmp     std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
.LC1:
        .string "Hello from Derived 2 "
main:
        sub     rsp, 8
        call    Derived1::say_hello_from_child() [clone .isra.0]
        mov     edx, 21
        mov     esi, OFFSET FLAT:.LC1
        mov     edi, OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)
        mov     edi, OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
        call    Derived1::say_hello_from_child() [clone .isra.0]
        xor     eax, eax
        add     rsp, 8
        ret
_GLOBAL__sub_I_main:
        sub     rsp, 8
        mov     edi, OFFSET FLAT:_ZStL8__ioinit
        call    std::ios_base::Init::Init() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:_ZStL8__ioinit
        mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
        add     rsp, 8
        jmp     __cxa_atexit