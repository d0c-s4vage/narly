// tokenizer.h
// N for gnarly!

#ifndef _TOKENIZER_H
#define _TOKENIZER_H

using namespace std;

class Tokenizer {
	public:
		Tokenizer(PCSTR inputText){
			_storageBuffLength = strlen(inputText)+1;
			_storageBuff = (PSTR) malloc(sizeof(CHAR) * _storageBuffLength);
			_inputStream << inputText;
		};
		~Tokenizer() {
			free(_storageBuff);
			_storageBuff =  NULL;
		};
		// fetches the next token from _inputStream and stores it into storageBuff, using
		// delim as the delimiter
		PSTR next(char delim) {
			memset((CHAR *)_storageBuff, 0, _storageBuffLength);
			if(!_inputStream.getline((CHAR *)_storageBuff, _storageBuffLength-1, delim)) {
				return NULL;
			}
			return _storageBuff;
		};

	private:
		stringstream _inputStream;
		PSTR _storageBuff;
		UINT _storageBuffLength;
};

#endif // _TOKENIZER_H