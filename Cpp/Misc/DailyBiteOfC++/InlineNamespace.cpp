#include <print>
#include <string>

namespace
{
    namespace MyLib
    {
        // You can use macros(compiler flag) here to decide expose V1 or V2 version.

        namespace V1
        {
            struct Order
            {
                int m_id;
                double m_price;
            };

            void Process(const Order &order)
            {
                std::println("[V1] Processing order[{}], price = {}", order.m_id, order.m_price);
            }
        }

        inline namespace V2
        {
            struct Order
            {
                int m_id;
                double m_price;
                double m_amount;
            };

            void Process(const Order &order)
            {
                std::println("[V2] Processing order[{}], price = {}, amount = {}", order.m_id, order.m_price, order.m_amount);
            }
        }
    }
}

int main()
{
    // Call V2 version
    MyLib::Order order{1, 2.2, 3.5};
    Process(order);

    // Call V1 version explicitly
    MyLib::V1::Order oldOrder{2, 3.3};
    Process(oldOrder);

    return 0;
}
