#include <iostream>
#include <string>
#include <stdexcept>
#include "API.h"

int main() {
	APIClient client("127.0.0.1", 3002);
	std::string set_response = client.setColor(1, 1, "#ff0000");
	std::string set_response1 = client.setColor(2, 2, "#ff0000");
	std::string set_response2 = client.setColor(3, 3, "#ff0000");
	std::string set_response3 = client.setColor(4, 4, "#ff0000");
	std::string set_response4 = client.setColor(5, 5, "#ff0000");
	return 0;
}
