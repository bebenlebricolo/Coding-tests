.LC0:
        .string "My name is : "
Base<Derived>::do_something():
        push    rbp
        mov     esi, OFFSET FLAT:.LC0
        mov     rbp, rdi
        mov     edi, OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
        mov     rsi, rbp
        mov     rdi, rax
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <char, std::char_traits<char>, std::allocator<char> >(std::basic_ostream<char, std::char_traits<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
        pop     rbp
        mov     rdi, rax
        jmp     std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
.LC1:
        .string "Base"
.LC2:
        .string "Derived"
.LC3:
        .string "Hello from Derived"
main:
        push    rbp
        mov     esi, OFFSET FLAT:.LC1
        mov     edx, OFFSET FLAT:.LC1+4
        sub     rsp, 32
        lea     rdi, [rsp+16]
        mov     QWORD PTR [rsp], rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_S_copy_chars(char*, char const*, char const*)
        mov     rax, QWORD PTR [rsp]
        mov     esi, OFFSET FLAT:.LC2
        mov     rdi, rsp
        mov     QWORD PTR [rsp+8], 4
        mov     BYTE PTR [rax+4], 0
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::operator=(char const*)
        jmp     .L15
        jmp     .L13
.L15:
        mov     esi, OFFSET FLAT:.LC3
        mov     edi, OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
        mov     rdi, rax
        call    std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
        mov     rdi, rsp
        call    Base<Derived>::do_something()
        mov     rdi, rsp
        call    Base<Derived>::do_something()
        mov     rdi, rsp
        call    Base<Derived>::do_something()
        mov     rdi, rsp
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_dispose()
        add     rsp, 32
        xor     eax, eax
        pop     rbp
        ret
.L13:
        mov     rbp, rax
        mov     rdi, rsp
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_dispose()
        mov     rdi, rbp
        call    _Unwind_Resume
_GLOBAL__sub_I_main:
        push    rax
        mov     edi, OFFSET FLAT:_ZStL8__ioinit
        call    std::ios_base::Init::Init() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:_ZStL8__ioinit
        pop     rcx
        mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
        jmp     __cxa_atexit