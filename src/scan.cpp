#include <string>
#include "data.hpp"

class Scanner {
	Data data;

	Scanner(Data data) {
		this.data = data;
	}	

	int chrpos(std::string s, char c) {
		return s.find(c)
	}

	char next() {
		char c;

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

	void put_back(char c) {
		this.data.putBack = c;
	}

	char skip() {
		char c;

		c = this.next();
		while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
			c = this.next();
		}
		
		return c;
	}

	int scan_int(char c) {
		int k;
		int val = 0;

		while ((k = this.chrpos("0123456789", c)) >= 0) {
		val = val * 10 + k;
		c = this.next();
		}

		this.put_back(c);
		return val;
	}


}
