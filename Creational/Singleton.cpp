#include <iostream>
#include <thread>
#include <mutex>

class Singleton
{
private:
    Singleton()
    {
        std::cout << "Singleton instance number " << count << " created\n";
    }

    Singleton(const Singleton& ) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
    static int count;
    static Singleton* SingletonPtr;
    static Singleton* getSingleton();
    static std::mutex mtx;
    
};

int Singleton::count = 0;
Singleton* Singleton::SingletonPtr = nullptr;
std::mutex Singleton::mtx;

Singleton* Singleton::getSingleton()
{   
    
    if(SingletonPtr == nullptr)
    {
        mtx.lock();
        if(SingletonPtr == nullptr)
        {
            count++;
            SingletonPtr = new Singleton();
        }
        mtx.unlock();
    }

    return SingletonPtr;
}

void createSingletonInstance()
{
    Singleton* sPtr = Singleton::getSingleton();
}


int main()
{

    std::thread t1(createSingletonInstance);
    
    // Should not create a new instance
    // Even in the case of multi-threaded scenario
    std::thread t2(createSingletonInstance);

    t1.join();
    t2.join();

    return 0;
}