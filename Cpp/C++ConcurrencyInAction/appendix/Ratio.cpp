#include <iostream>
#include <ratio>

int main(int argc, char *argv[])
{
    using namespace std;

    using res1 = ratio_add<ratio<1, 2>, ratio<1, 3>>;
    cout << "1/2 + 1/3 = " << res1::num << "/" << res1::den << "\n";

    using res2 = ratio_subtract<ratio<1, 2>, ratio<1, 3>>;
    cout << "1/2 - 1/3 = " << res2::num << "/" << res2::den << "\n";

    using res3 = ratio_multiply<ratio<1, 2>, ratio<1, 3>>;
    cout << "1/2 * 1/3 = " << res3::num << "/" << res3::den << "\n";

    using res4 = ratio_add<ratio<1, 2>, ratio<1, 3>>;
    cout << "1/2 / 1/3 = " << res4::num << "/" << res4::den << "\n";

    return EXIT_SUCCESS;
}
