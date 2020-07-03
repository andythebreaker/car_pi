#include "include/curlpp/cURLpp.hpp"
#include "include/curlpp/Options.hpp"
#include "include/curlpp/Easy.hpp"
#include <string>

using namespace std;
using namespace curlpp::options;

int main(){
  cout<<"start"<<endl;
  try{
    curlpp::Cleanup myCleanup;
    curlpp::Easy myRequest;
    myRequest.setOpt<Url>("http://api.zhconvert.org");
    myRequest.perform();
  }catch(curlpp::RuntimeError & e){
    cout<< e.what()<<endl;
  }
   /* ostringstream os;
  os<<curlpp::options::Url("http://wikipedia.org");
  string wtf = os.str();
  cout<<wtf;
  */
  return 0;
}
