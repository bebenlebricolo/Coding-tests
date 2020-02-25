.LC0:
        .string "Hello from "
Derived::do_something():
        push    rbx
        mov     esi, OFFSET FLAT:.LC0
        mov     rbx, rdi
        mov     edi, OFFSET FLAT:_ZSt4cout
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
        lea     rsi, [rbx+8]
        mov     rdi, rax
        call    std::basic_ostream<char, std::char_traits<char> >& std::operator<< <char, std::char_traits<char>, std::allocator<char> >(std::basic_ostream<char, std::char_traits<char> >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
        pop     rbx
        mov     rdi, rax
        jmp     std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
do_some_stuff_with_base(Base*):
        mov     rax, QWORD PTR [rdi]
        jmp     [QWORD PTR [rax]]
.LC1:
        .string "Base"
.LC2:
        .string "Derived"
main:
        push    rbp
        mov     esi, OFFSET FLAT:.LC1
        mov     edx, OFFSET FLAT:.LC1+4
        sub     rsp, 48
        mov     QWORD PTR [rsp+8], OFFSET FLAT:vtable for Base+16
        lea     rdi, [rsp+32]
        mov     QWORD PTR [rsp+16], rdi
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_S_copy_chars(char*, char const*, char const*)
        mov     rax, QWORD PTR [rsp+16]
        mov     esi, OFFSET FLAT:.LC2
        mov     QWORD PTR [rsp+24], 4
        lea     rdi, [rsp+16]
        mov     BYTE PTR [rax+4], 0
        mov     QWORD PTR [rsp+8], OFFSET FLAT:vtable for Derived+16
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::operator=(char const*)
        jmp     .L16
        jmp     .L14
.L16:
        lea     rdi, [rsp+8]
        call    Derived::do_something()
        lea     rdi, [rsp+8]
        call    Derived::do_something()
        lea     rdi, [rsp+8]
        call    do_some_stuff_with_base(Base*)
        mov     QWORD PTR [rsp+8], OFFSET FLAT:vtable for Base+16
        lea     rdi, [rsp+16]
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_dispose()
        add     rsp, 48
        xor     eax, eax
        pop     rbp
        ret
.L14:
        mov     rbp, rax
        mov     QWORD PTR [rsp+8], OFFSET FLAT:vtable for Base+16
        lea     rdi, [rsp+16]
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_M_dispose()
        mov     rdi, rbp
        call    _Unwind_Resume
_GLOBAL__sub_I_do_some_stuff_with_base(Base*):
        push    rax
        mov     edi, OFFSET FLAT:_ZStL8__ioinit
        call    std::ios_base::Init::Init() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:_ZStL8__ioinit
        pop     rcx
        mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
        jmp     __cxa_atexit
typeinfo name for Base:
        .string "4Base"
typeinfo for Base:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for Base
typeinfo name for Derived:
        .string "7Derived"
typeinfo for Derived:
        .quad   vtable for __cxxabiv1::__si_class_type_info+16
        .quad   typeinfo name for Derived
        .quad   typeinfo for Base
vtable for Base:
        .quad   0
        .quad   typeinfo for Base
        .quad   __cxa_pure_virtual
vtable for Derived:
        .quad   0
        .quad   typeinfo for Derived
        .quad   Derived::do_something()