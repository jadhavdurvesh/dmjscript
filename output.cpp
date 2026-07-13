#include <iostream>
#include <string>
using namespace std;


int main()
{
    int status = 13;
    digitalWrite(status, HIGH);
    delay(1000);
    digitalWrite(status, LOW);
    return 0;
}
