//-----------------------------------------------------
// Design Name : Server Side Socket
// File Name   : FileProccess.hpp
// Function    : Handel Recieved File
// Coder       : Amirreza Tavakoli
//-----------------------------------------------------
#ifndef FileProccess
#define FileProccess
#include<fstream>
#include<iterator>
#include<sstream>
#include<string>
#include <algorithm>
using namespace std;
class FileHandler
{
public:
	static string GetFileName(string path)
	{
		for (int i = path.length(); i >= 0; i--)
			if (path[i] == '\\')
				return path.substr(i + 1);
		return path;
	}
	static string GetFileExtention(string path)
	{
		string filename = GetFileName(path);
		size_t i = filename.rfind('.', filename.length());
		if (i != string::npos) {
			return(filename.substr(i, filename.length() - i));
		}
	}
	static string GetFileNameWhitOutExtention(string path)
	{
		string filename = GetFileName(path);
		size_t i = filename.rfind('.', filename.length());
		if (i != string::npos) {
			return(filename.substr(0, i));
		}
	}
	static inline string TempPath(string Filename, string Extention = ".tmp")
	{
		return Filename + Extention;
	}
	static inline bool IsFileExist(const string& name) {
		ifstream f(name.c_str());
		return f.good();
	}
	static bool ConvertTmpToStableFile(const string& tmppath, const string& destinationpath)
	{
		if (!IsFileExist(tmppath))
			return 0;
		if (rename(tmppath.c_str(), destinationpath.c_str()) != 0)
			ConvertTmpToStableFile(tmppath, GetFileNameWhitOutExtention(destinationpath) + "_Copy" + GetFileExtention(destinationpath));
		else
			return 1;
	}
};

class WriteRecievedFile
{
public:
	string FileExtention;
	string FileName;
	long TotalSize;
	long CurrentPos;
	ofstream ofstmp;
	WriteRecievedFile(string FileName , string FileExtention, long totalSize)
	{
		ofstmp.open(FileHandler::TempPath(FileName), ios::binary);
		CurrentPos = 0;
		TotalSize = totalSize;
		this->FileExtention = FileExtention;
		this->FileName = FileName;
	}
	void StartWrite(char* Buffer , long RecievedBufferSize)
	{
		ofstmp.write(Buffer, RecievedBufferSize);
		CurrentPos += RecievedBufferSize;
		if (!(CurrentPos < TotalSize))
		{
			ofstmp.close();
			FileHandler::ConvertTmpToStableFile(FileHandler::TempPath(FileName), FileName+ FileExtention);
			std::clog << "[Log]:  Finish Recieving File \n";

		}
	}
};


#endif // !FileProccess
