#ifndef STEMHELPER_H
#define STEMHELPER_H

#include "PorterStemmer.h"
#include <cstring>

class StemHelper
{
	public:
		static std::string stemword(char* buffer)
		{
			struct stemmer * z = create_stemmer();
			int stringEnd = stem(z, buffer, strlen(buffer)-1);
            buffer[stringEnd+ 1] = '\0';
            //free(*z);
            return buffer;
		}
	private:
};

#endif
