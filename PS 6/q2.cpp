#include <iostream>
#include "user.h"
#include "password.h"


using namespace Authenticate;
using std::cout;
using std::endl;

int main() {
  inputUserName();
  inputPassword();
  cout << "Your username is " << getUserName() <<
          " and your password is: " <<
    getPassword() << endl; return 0;
}