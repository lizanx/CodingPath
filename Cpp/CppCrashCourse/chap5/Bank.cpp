#include <iostream>
#include <map>
#include <utility>

struct Logger
{
    virtual ~Logger() = default;
    virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger : Logger
{
    ConsoleLogger() {}
    ConsoleLogger(const char *tag): tag{ tag } {}
    void log_transfer(long from, long to, double amount) override
    {
        std::cout << "[cons] " << "[" << tag << "] "
            << from << " -> " << to << ": " << amount << "\n";
    }

private:
    std::string tag{};
};

struct FileLogger : Logger
{
    void log_transfer(long from, long to, double amount) override
    {
        std::cout << "[file] " << from << "," << to << "," << amount << "\n";
    }
};

struct AccountDatabase
{
    virtual std::pair<double, bool> get_amount(long id) = 0;
    virtual bool set_amount(long id, double amount) = 0;
    virtual void show_all() {}
    virtual ~AccountDatabase() = default;
};

struct  InMemoryAccountDatabase : AccountDatabase
{
    InMemoryAccountDatabase(): database{} {}
    InMemoryAccountDatabase(std::map<long, double> m): database{ m } {}
    ~InMemoryAccountDatabase() override = default;

    std::pair<double, bool> get_amount(long id) override
    {
        if (auto account = database.find(id); account != database.end())
        {
            return { account->second, true };
        }
        return { 0.0, false };
    }
    bool set_amount(long id, double amount) override
    {
        if (auto account = database.find(id); account != database.end())
        {
            account->second = amount;
            return true;
        }
        return false;
    }

    void show_all() override
    {
        for (auto item : database)
        {
            std::cout << "[ID] " << item.first << "\t: [Amount] " << item.second << "\n";
        }
    }

private:
    std::map<long, double> database;
};


struct Bank
{
    Bank(AccountDatabase& db): accountDatabase{ db } {}
    Bank(AccountDatabase& db, Logger* logger): accountDatabase{ db }, logger{ logger } {}

    void set_logger(Logger *new_logger)
    {
        logger = new_logger;
    }
    void make_transfer(long from, long to, double amount)
    {
        if (logger)
            logger->log_transfer(from, to, amount);
        
        auto from_account = accountDatabase.get_amount(from);
        auto to_account = accountDatabase.get_amount(to);
        if (from_account.second && to_account.second && from_account.first >= amount)
        {
            accountDatabase.set_amount(from, from_account.first - amount);
            accountDatabase.set_amount(to, to_account.first + amount);
            std::cout << "Tranfer successfully\n";
        }
    }

    void display()
    {
        accountDatabase.show_all();
    }

private:
    Logger *logger{};
    AccountDatabase& accountDatabase;
};

int main()
{
    ConsoleLogger console_logger;
    FileLogger file_logger;
    std::map<long, double> db {
        { 1000, 50.0 },
        { 2000, 100.0 },
        { 4000, 200.0 }
    };
    InMemoryAccountDatabase inMemAccountDb{ db };
    Bank bank{ inMemAccountDb };
    bank.display();

    bank.set_logger(&console_logger);
    bank.make_transfer(1000, 2000, 49.95);
    bank.set_logger(&file_logger);
    bank.make_transfer(2000, 4000, 20.00);

    std::cout << "\n\nBank:\n";
    bank.display();

    return EXIT_SUCCESS;
}
