#include <string>
#include "data.hpp"

class Scanner {
	Data data;

	Scanner(Data data) {
		this.data = data;
	}	
	
	int next(void) {
		int c;

		if (this.data.putBack) {
			c = this.data.putBack;
			this.data.putBack = 0;
			return c;
		}

		this.data.inFile.open(this.data.fileName);
		c = getc(this.data.inFile);
		if ('\n' == c) {
			this.data.line++;
		}
		this.data.inFile.close();
		return c;
	}
}
