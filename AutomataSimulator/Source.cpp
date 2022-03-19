#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"AutomataSimulator.h"
int main()
{
	std::ifstream ifst;
	AutomataSimulator as;
	ifst.open("TextData.txt");
	as.setifstreamfile(ifst);
	std::cout << " result = " << as.run("abcabcdeffffdaaaadffffff") << std::endl;
	ifst.close();
	ifst.open("TextData2.txt");
	as.clear();
	as.setifstreamfile(ifst);
	std::cout << " result = " << as.run("abbbabababbababbabbba") << std::endl;;


	return 0;
}