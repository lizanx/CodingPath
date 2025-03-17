#include <functional>
#include <iostream>
#include <string>
#include <type_traits>

namespace
{
    class Cls
    {
    public:
        int Id{};
        void MemFn()
        {
            std::cout << "Cls::MemFn()\n";
        }
        static void StaticMemFn()
        {
            std::cout << "Cls::StaticMemFn()\n";
        }
    };

    void NonMemFn()
    {
        std::cout << "NonMemFn()\n";
    }

    enum class EnumClassColor
    {
        Red,
        Green,
        Blue,
    };

    enum EnumColor
    {
        Red,
        Green,
        Blue,
    };

    union IntDoubleUnion
    {
        int IntValue;
        double DoubleValue;
    };

    class Base
    {
    public:
        virtual void VirtualFn() = 0;
    };

    class Derived : public Base
    {
    public:
        void VirtualFn() override
        {
            std::cout << "Derived::VirtualFn()\n";
        }
    };
}

int main()
{
    using std::cout;
    cout << std::boolalpha;

    using VoidAlias = void;
    cout << "'VoidAlias' is void? " << std::is_void_v<VoidAlias> << "\n";
    cout << "'int' is void? " << std::is_void_v<int> << "\n\n";

    using IntAlias = int;
    cout << "'IntAlias' is integral? " << std::is_integral_v<IntAlias> << "\n";
    cout << "'char' is integral? " << std::is_integral_v<char> << "\n";
    cout << "'double' is integral? " << std::is_integral_v<double> << "\n\n";

    using DoubleAlias = double;
    cout << "'DoubleAlias' is floating point? " << std::is_floating_point_v<DoubleAlias> << "\n";
    cout << "'float' is floating point? " << std::is_floating_point_v<float> << "\n";
    cout << "'int' is floating point? " << std::is_floating_point_v<int> << "\n\n";

    using Int3Array = int[3];
    using Double100Array = double[100];
    cout << "'Int3Array' is array? " << std::is_array_v<Int3Array> << "\n";
    cout << "'Double100Array' is array? " << std::is_array_v<Double100Array> << "\n";
    cout << "'long long' is array? " << std::is_array_v<long long> << "\n";
    cout << "'int*' is array? " << std::is_array_v<int *> << "\n\n"; // false

    using IntPtr = int *;
    cout << "'IntPtr' is pointer? " << std::is_pointer_v<IntPtr> << "\n";
    cout << "'void*' is pointer? " << std::is_pointer_v<void *> << "\n";
    cout << "'Int3Array' is pointer? " << std::is_pointer_v<Int3Array> << "\n\n"; // false

    using IntRef = int &;
    using IntRRef = int &&;
    cout << "'IntRef' is l-ref? " << std::is_lvalue_reference_v<IntRef> << "\n";
    cout << "'IntRef' is r-ref? " << std::is_rvalue_reference_v<IntRef> << "\n";
    cout << "'IntRRef' is l-ref? " << std::is_lvalue_reference_v<IntRRef> << "\n";
    cout << "'IntRRef' is r-ref? " << std::is_rvalue_reference_v<IntRRef> << "\n\n";

    {
        Cls obj{};
        int Cls::*memObjPtr = &Cls::Id;
        int i{};
        int *nonMemObjPtr{&i};
        auto memFnPtr = &Cls::MemFn;
        auto nonMemFnPtr = &NonMemFn;

        cout << "'memObjPtr' is member object pointer? " << std::is_member_object_pointer_v<decltype(memObjPtr)> << "\n";
        cout << "'nonMemObjPtr' is member object pointer? " << std::is_member_object_pointer_v<decltype(nonMemObjPtr)> << "\n";
        cout << "'memFnPtr' is member function pointer? " << std::is_member_function_pointer_v<decltype(memFnPtr)> << "\n";
        cout << "'nonMemFnPtr' is member function pointer? " << std::is_member_function_pointer_v<decltype(nonMemFnPtr)> << "\n\n";
    }

    cout << "'EnumClassColor' is enum? " << std::is_enum_v<EnumClassColor> << "\n";
    cout << "'EnumColor' is enum? " << std::is_enum_v<EnumColor> << "\n\n";

    cout << "'IntDoubleUnion' is union? " << std::is_union_v<IntDoubleUnion> << "\n";
    cout << "'Cls' is union? " << std::is_union_v<Cls> << "\n\n";

    cout << "'Cls' is class? " << std::is_class_v<Cls> << "\n";
    cout << "'IntDoubleUnion' is class? " << std::is_class_v<IntDoubleUnion> << "\n\n";

    {
        using FnPtrType = void (*)();
        using FnType = std::function<void()>;
        class Functor
        {
        public:
            void operator()()
            {
            }
        };

        cout << "'NonMemFn' is function? " << std::is_function_v<decltype(NonMemFn)> << "\n";                 // true
        cout << "'Cls::StaticMemFn' is function? " << std::is_function_v<decltype(Cls::StaticMemFn)> << "\n"; // true
        cout << "'&Cls::MemFn' is function? " << std::is_function_v<decltype(&Cls::MemFn)> << "\n";           // false
        cout << "'FnPtrType' is function? " << std::is_function_v<FnPtrType> << "\n";                         // false
        cout << "'FnType' is function? " << std::is_function_v<FnType> << "\n";                               // false
        cout << "'Functor' is function? " << std::is_function_v<Functor> << "\n";                             // false
        cout << "'Cls' is function? " << std::is_function_v<Cls> << "\n\n";                                   // false
    }

    cout << "'const int' is const? " << std::is_const_v<const int> << "\n";
    cout << "'int' is const? " << std::is_const_v<int> << "\n\n";

    using VolatileInt = volatile int;
    cout << "'VolatileInt' is volatile? " << std::is_volatile_v<VolatileInt> << "\n";
    cout << "'int' is volatile? " << std::is_volatile_v<int> << "\n\n";

    cout << "'int' is trivial? " << std::is_trivial_v<int> << "\n";
    cout << "'double' is trivial? " << std::is_trivial_v<double> << "\n";
    cout << "'string' is trivial? " << std::is_trivial_v<std::string> << "\n";
    cout << "'Cls' is trivial? " << std::is_trivial_v<Cls> << "\n\n";

    using Point = struct
    {
        int X;
        int Y;
    };
    cout << "'Point' is PlainOldData? " << std::is_pod_v<Point> << "\n";
    cout << "'Cls' is PlainOldData? " << std::is_pod_v<Cls> << "\n\n";

    cout << "'Cls' is polymorphic? " << std::is_polymorphic_v<Cls> << "\n";
    cout << "'Base' is polymorphic? " << std::is_polymorphic_v<Base> << "\n";
    cout << "'Derived' is polymorphic? " << std::is_polymorphic_v<Derived> << "\n\n";

    cout << "'Base' is abstract? " << std::is_abstract_v<Base> << "\n";
    cout << "'Derived' is abstract? " << std::is_abstract_v<Derived> << "\n\n";

    cout << "'Base*' can be assigned from 'Derived*'? " << std::is_assignable_v<Base *&, Derived *> << "\n"; // Must use "Base*&", since "Base*" is r-value type which cannot be assigned to.
    cout << "'Base&' can be assigned from 'Derived&'? " << std::is_assignable_v<Base &, Derived &> << "\n";
    cout << "'Derived*' can be assigned from 'Base*'? " << std::is_assignable_v<Derived *&, Base *> << "\n";
    cout << "'Derived&' can be assigned from 'Base&'? " << std::is_assignable_v<Derived &, Base &> << "\n\n";

    cout << "'IntPtr' is the same as 'int*'? " << std::is_same_v<IntPtr, int *> << "\n\n";

    cout << "'Derived' is base of 'Base'? " << std::is_base_of_v<Derived, Base> << "\n";
    cout << "'Base' is base of 'Derived'? " << std::is_base_of_v<Base, Derived> << "\n\n";

    cout << "'int' implicitly convertible to 'long'? " << std::is_convertible_v<int, long> << "\n";
    cout << "'int' implicitly convertible to 'char'? " << std::is_convertible_v<int, char> << "\n";
    cout << "'int' implicitly convertible to 'char*'? " << std::is_convertible_v<int, char *> << "\n";
    cout << "'Derived*' implicitly convertible to 'Base*'? " << std::is_convertible_v<Derived *, Base *> << "\n";
    cout << "'Base*' implicitly convertible to 'Derived*'? " << std::is_convertible_v<Base *, Derived *> << "\n";
    cout << "'Derived&' implicitly convertible to 'Base&'? " << std::is_convertible_v<Derived &, Base &> << "\n\n";
}
