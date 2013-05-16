#include <iostream>
#include "HexMesh.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " input.grid output.grid\n";
		exit(-1);
	}

	return 0;
}