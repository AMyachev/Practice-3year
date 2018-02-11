#include "graph.h"

#include <fstream>

/*numbering of vertices from the number one*/

int main() {
	std::ifstream fin("C:\\example\\practice.txt");
	std::istream_iterator<int16_t> iter(fin);
	graph grh(iter);
	characteristics v_chr(iter);
	if (verify_input_data(grh, v_chr) == false) std::cout << "input data do not satisfy the restriction of injection" << std::endl;
	grh.print();
	std::sort(v_chr.begin(), v_chr.end(), [](int first, int second) {return first < second; });
	
	/*try {

		for (int i = 0; i < v_chr.size(); ++i)
			std::cout << v_chr[i] << " ";
		std::cout << std::endl;
	}
	catch (bad_input) {
		std::cout << "input data do not satisfy the restriction of injection" << std::endl;
	}*/
	system("pause");
	return 0;
}