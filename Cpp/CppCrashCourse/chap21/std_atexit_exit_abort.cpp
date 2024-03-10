#include <iostream>
#include <string>

struct Tracer
{
    Tracer(std::string name_in) : name{ std::move(name_in) }
    {
        std::cout << name << " constructed\n";
    }

    ~Tracer()
    {
        std::cout << name << " destructed.\n";
    }

private:
    std::string name;
};

Tracer staticTracer{ "Static tracer" };

void run()
{
    std::cout << "Registering atexit callback.\n";
    std::atexit([] { std::cout << "*** Executing std::atexit callback function. ***\n"; });
    std::cout << "Callback registered.\n";
    // std::exit(0); // !!! this won't destruct localTracer and `delete dynamicTracer` won't execute.
    std::abort(); // !!! None of destructors will be called, no callback called either.
}

int main()
{
    std::cout << "Entering main()\n";

    Tracer localTracer{ "Local Tracer" };
    thread_local Tracer threadLocalTracer{ "Thread Local Tracer" };
    const auto* dynamicTracer{ new Tracer{ "Dynamic Tracer" } };

    run();

    delete dynamicTracer;
    
    std::cout << "Exiting main()\n";
}