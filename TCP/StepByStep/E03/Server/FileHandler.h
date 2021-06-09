#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
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
	static inline string Combine(string str1, string str2)
	{
		return str1 + "\\" + str2;
	}
	static inline string TempPath(string Filename, string Extention = ".tmp")
	{
		while (IsFileExist(Filename + Extention))
			Filename += "_copy";
		return Filename + Extention;

	}
	static inline bool IsFileExist(const string& name) {
		ifstream f(name.c_str());
		return f.good();
	}
	static bool ConvertTmpToStableFile(const string& tmppath, const string& destinationpath)
	{
		string fname;
		if (GetFileNameWhitOutExtention(destinationpath) != "")
			fname = GetFileNameWhitOutExtention(destinationpath) + GetFileExtention(destinationpath);
		else
			fname = GetFileNameWhitOutExtention(tmppath) + GetFileExtention(destinationpath);

		if (!IsFileExist(tmppath))
			return 0;

		if (rename(tmppath.c_str(), fname.c_str()) != 0)
			ConvertTmpToStableFile(tmppath, GetFileNameWhitOutExtention(fname) + "_Copy" + GetFileExtention(destinationpath));
		else
			return 1;
	}
};
#endif