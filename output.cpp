#include <iostream>
#include <string>
using namespace std;


int main()
{
    Servo arm;
    arm.attach(9);
    arm.write(0);
    delay(1000);
    arm.write(90);
    delay(1000);
    arm.write(180);
    return 0;
}
