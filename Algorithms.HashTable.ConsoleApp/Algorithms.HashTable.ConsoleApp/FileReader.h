
#include "iostream"

static class FileReader
{
public:
	static int elementsToBeGenerated;
	static int k1;
	static int k2;
	static int k3;
	static int k4;

	static int ReadFile(const char* filePath)
	{
		FILE* fp = fopen(filePath, "r");
		if (fp == NULL)
			return -1;
		fscanf(fp, "%d %d %d %d %d", &elementsToBeGenerated, &k1, &k2, &k3, &k4);
		fclose(fp);
		std::cout << "Numbers read from file:" << elementsToBeGenerated << " " << " " << k1 << " " << k2 << " " << k3 << " " << k4 << " " << std::endl;
	}

};

int FileReader::elementsToBeGenerated = 0;
int FileReader::k1 = 0;
int FileReader::k2 = 0;
int FileReader::k3 = 0;
int FileReader::k4 = 0;