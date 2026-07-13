#include <iostream>
#include <string>
using namespace std;


void greet()
{
    cout << "Hello from function" << endl;
}

int main()
{
    cout << "Start" << endl;
    greet();
    for(int i = 0; i < 2; i++)
    {
        cout << "Loop" << endl;
    }
    cout << "End" << endl;
    return 0;
}
