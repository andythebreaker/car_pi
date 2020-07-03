/**
* \file
* The most simple example.
* 
*/

#include "include/curlpp/cURLpp.hpp"
#include "include/curlpp/Easy.hpp"
#include "include/curlpp/Options.hpp"


using namespace curlpp::options;

int main(int, char **)
{
	try
	{
		// That's all that is needed to do cleanup of used resources (RAII style).
		curlpp::Cleanup myCleanup;

		// Our request to be sent.
		curlpp::Easy myRequest;

		// Set the URL.
		myRequest.setOpt<Url>("http://api.zhconvert.org");

		// Send request and get a result.
		// By default the result goes to standard output.
		myRequest.perform();
	}

	catch(curlpp::RuntimeError & e)
	{
		std::cout << e.what() << std::endl;
	}

	catch(curlpp::LogicError & e)
	{
		std::cout << e.what() << std::endl;
	}
    
  return 0;
}
