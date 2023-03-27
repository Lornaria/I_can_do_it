#pragma once
#include <fstream>
#include <string>

class FileLogger{
private:
	std::ofstream logOut;
public:
	FileLogger(const std::string& fn){
		logOut.open(fn, std::ios_base::out);
	}
	~FileLogger(){
		if (logOut.is_open())
		{
			logOut.close();
		}
	}
	std::string GetCurDateTime();
	void Write(const std::string& str);
	void Write(const std::string& str, int n);
	void Write(const std::string& str, double d);

};

