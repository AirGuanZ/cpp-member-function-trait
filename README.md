# MemberFunctionTrait

Trait classes for C++ member function pointer type

* header-only
* C++11-compatible
* support const/volatile/reference qualifiers and variadic function

## Usage

```cpp
member_function_pointer_trait<decltype(&Class::MemberFunction)>::
    class_type
    return_type
    arg_types // tuple of arguments, exists when has_va_args is false
    arg<I>
    has_va_args // is declared with '...'
    has_const_qualifier
    has_volatile_qualifier
    has_lvalue_ref_qualifier
    has_rvalue_ref_qualifier
```

## Example

```cpp
class A
{
public:
    void f1(const int &z) const;
    void f2(...) volatile &;
};
member_function_pointer_trait<decltype(&A::f1)>::arg<0>                   -> const int &
member_function_pointer_trait<decltype(&A::f1)>::has_const_qualifier      -> true
member_function_pointer_trait<decltype(&A::f2)>::has_va_args              -> true
member_function_pointer_trait<decltype(&A::f2)>::has_volatile_qualifier   -> true
member_function_pointer_trait<decltype(&A::f2)>::has_rvalue_ref_qualifier -> true
```
