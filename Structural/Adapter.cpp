#include <iostream>
#include <string>
#include <algorithm>

class Target
{
public:
    virtual ~Target() = default;
    virtual void request(const std::string& text)
    {
        std::cout << "Target: I print the text as given \n";
        std::cout << text << std::endl;
    }
};

class Adaptee
{
public:
    void request(const std::string& text)
    {
        std::cout << "Adaptee: I print the text in reverse \n";
        std::string reverseText = text;
        std::reverse(reverseText.begin(), reverseText.end());
        std::cout << reverseText << std::endl;

    }
};

class Adapter : public Target
{
private:
    Adaptee* adaptee_;
public:
    Adapter(Adaptee* adaptee)
        :adaptee_(adaptee)
        {}

    void request(const std::string& text) override
    {
        std::cout << "Adapter: I convert the text in a format suitable for Adaptee \n";
        std::string reverseText = text;
        std::reverse(reverseText.begin(), reverseText.end());
        adaptee_->request(reverseText);
    }

    
};

void Client(Target* target)
{   
    std::string text{"This is adapter design pattern"};
    target->request(text);
}


int main()
{

    Target* target = new Target();
    Client(target);

    Adaptee* adaptee = new Adaptee();
    adaptee->request(std::string("This is adapter design pattern"));

    Adapter* adapter = new Adapter(adaptee);
    Client(adapter);

    return 0;
}