#include <memory>
#include <print>

namespace
{
    class IService
    {
    public:
        virtual void DoAction() = 0;
        virtual ~IService() = default;
    };

    class FakeService : public IService
    {
    public:
        void DoAction() override
        {
            std::println("Doing action from fake service.");
        }
    };

    class ProductionService : public IService
    {
    public:
        void DoAction() override
        {
            std::println("Doing action from production service.");
        }
    };

    class ActionDoer
    {
    public:
        ActionDoer(std::unique_ptr<IService> service) : m_service{std::move(service)}
        {
        }

        void operator()()
        {
            if (m_service)
                m_service->DoAction();
        }

    private:
        std::unique_ptr<IService> m_service;
    };

    void TestCase()
    {
        std::println("<<<<< Test Case >>>>>");
        ActionDoer ad{std::make_unique<FakeService>()};
        ad();
    }

    void ProductionCase()
    {
        std::println("<<<<< Production Case >>>>>");
        ActionDoer ad{std::make_unique<ProductionService>()};
        ad();
    }
}

int main()
{
    ProductionCase();
    TestCase();

    return 0;
}
