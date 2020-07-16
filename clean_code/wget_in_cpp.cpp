//using .h github.com/yhirose/cpp-httplib

#include <iostream>
#include <string>
#include "httplib.h"

using namespace std;

int main(){
  cout<<"start"<<endl;
  httplib::Client cli("api.zhconvert.org",80);

  auto res = cli.Get("/convert?converter=Pinyin&text=這是一格測試的請求&prettify=1");
  if (res && res->status == 200){
    cout<<res->body<<endl;
  }
  cout<<"stop"<<endl;
}
