#include "mem_fn_traits.h"

class A
{
public:

    int f1(int x, float y);

    void f2(const int &z) const &&;

    void f3(...) volatile &;
};

#define TRAIT(FN_PTR) member_function_pointer_trait<decltype(FN_PTR)>
#define SASSERT(COND) static_assert(COND, "")
#define SASSERT_SAME(A, B) static_assert(std::is_same_v<A, B>, "")

int main()
{
    SASSERT_SAME(TRAIT(&A::f1)::class_type, A);
    SASSERT_SAME(TRAIT(&A::f1)::return_type, int);
    SASSERT_SAME(TRAIT(&A::f1)::arg<0>, int);
    SASSERT(!TRAIT(&A::f1)::has_va_args);
    SASSERT(!TRAIT(&A::f1)::has_const_qualifier);
    SASSERT(!TRAIT(&A::f1)::has_volatile_qualifier);
    SASSERT(!TRAIT(&A::f1)::has_lvalue_ref_qualifier);
    SASSERT(!TRAIT(&A::f1)::has_rvalue_ref_qualifier);

    SASSERT_SAME(TRAIT(&A::f2)::return_type, void);
    SASSERT_SAME(TRAIT(&A::f2)::arg<0>, const int &);
    SASSERT(!TRAIT(&A::f2)::has_va_args);
    SASSERT(TRAIT(&A::f2)::has_const_qualifier);
    SASSERT(!TRAIT(&A::f2)::has_volatile_qualifier);
    SASSERT(!TRAIT(&A::f2)::has_lvalue_ref_qualifier);
    SASSERT(TRAIT(&A::f2)::has_rvalue_ref_qualifier);

    SASSERT(TRAIT(&A::f3)::has_va_args);
    SASSERT(!TRAIT(&A::f3)::has_const_qualifier);
    SASSERT(TRAIT(&A::f3)::has_volatile_qualifier);
    SASSERT(TRAIT(&A::f3)::has_lvalue_ref_qualifier);
    SASSERT(!TRAIT(&A::f3)::has_rvalue_ref_qualifier);
}
