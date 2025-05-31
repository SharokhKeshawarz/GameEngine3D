#include "app.hpp"

int main()
{
    std::cout << "Application Started...\n";
    try {
        App app;
        app.Init();
        app.Run();
        app.Destroy();
    } catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "Unknown exception: " << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Application exiting...\n";
    return EXIT_SUCCESS;
}
