#include "md5.h"
#include <iostream>

using namespace std;

void PrintMD5(const string& str, MD5& md5) {
	cout << "MD5(\"" << str << "\") = " << md5.toString() << endl;
}

string FileDigest(const string& file) {

	ifstream in(file.c_str(), ios::binary);
	if (!in) {
		return "";
	}

	MD5 md5;
	std::streamsize length;
	char buffer[1024];
	while (!in.eof()) {
		in.read(buffer, 1024);
		length = in.gcount();
		if (length > 0) {
			md5.update(buffer, length);
		}
	}
	in.close();
	return md5.toString();
}

int main() {

	//cout << MD5("abc").toString() << endl;
	//cout << MD5(ifstream("D:\\test.txt")).toString() << endl;
	//cout << MD5(ifstream("D:\\test.exe", ios::binary)).toString() << endl;
	//cout << FileDigest("D:\\test.exe") << endl;
	/*
	MD5("") = d41d8cd98f00b204e9800998ecf8427e
	MD5("a") = 0cc175b9c0f1b6a831c399e269772661
	MD5("abc") = 900150983cd24fb0d6963f7d28e17f72
	MD5("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
	MD5("message digest") = f96b697d7cb7938d525a2f31aaf161d0
	MD5("D:\test.txt") = 7ac66c0f148de9519b8bd264312c4d64


	*/
	MD5 md5;
	md5.update("");
	PrintMD5("", md5);

	md5.update("a");
	PrintMD5("a", md5);

	md5.update("bc");
	PrintMD5("abc", md5);

	md5.update("defghijklmnopqrstuvwxyz");
	PrintMD5("abcdefghijklmnopqrstuvwxyz", md5);

	md5.reset();
	md5.update("message digest");
	PrintMD5("message digest", md5);

	//md5.reset();
	//md5.update(ifstream("D:\\test.txt"));
	//PrintMD5("D:\\test.txt", md5);
	return 0;
}
