#include <hip/hip_runtime.h>
#include <iostream>

int main () {
	int deviceCount = 0;
	hipError_t error = hipGetDeviceCount (&deviceCount);
	if (error != hipSuccess) {
		std::cout << "HIP Error: " << hipGetErrorString (error) << std::endl;
		return 1;
	}
	std::cout << "Found " << deviceCount << " HIP device(s)." << std::endl;
	for (int i = 0; i < deviceCount; i++) {
		hipDeviceProp_t props;
		hipGetDeviceProperties (&props, i);
		std::cout << "Device " << i << ": " << props.name << std::endl;
	}
	return 0;
}