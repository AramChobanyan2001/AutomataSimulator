#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
class AutomataSimulator
{
	
	std::vector<std::string> m_InputSymbol;
	std::vector<std::string> m_OutputSymbol;
	std::vector<std::string> m_InternalStates;
	std::vector<std::vector<std::pair<char, int>>> m_matrix;
    void SetSymbolandStates(const std::string& str,int k);//k == 0 -> m_InputSymbol|k == 1 -> m_OutputSymbol|k == 2 -> m_InternalStates
	void Setmatrix(const std::string& str);
public:
	void setifstreamfile(std::ifstream& ifst);
	std::string run(const std::string& str);
	void clear();


};

inline void AutomataSimulator::setifstreamfile(std::ifstream& ifst)
{
	if (!ifst.is_open())
	{
		
		std::cerr << "error ifstream file is not open" << std::endl;
	}
	else
	{
		int iter = 0;
		std::string str;
		while (!ifst.eof())
		{
			ifst >> str;
			if (iter <= 2)
			{
				this->SetSymbolandStates(str, iter);
			}
			else
			{
				this->Setmatrix(str);
			}
			++iter;
			//std::cout << iter << "   =   " << str << std::endl;
		}
		/*for (auto& t : m_matrix)
		{
			for (auto& y : t)
			{
				std::cout << y.first << ',' << y.second << " | ";
			}
			std::cout << std::endl;
		}*/
	}
}

inline std::string AutomataSimulator::run(const std::string& str)
{
	std::string result;
	int q = 0;
	for (const auto & s:str)
	{
		int index = -1;
		for (int i = 0;i < m_InputSymbol.size();++i)
		{
			if (s == m_InputSymbol.at(i).at(0))
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			result.push_back(m_matrix.at(q).at(index).first);
			q = m_matrix.at(q).at(index).second;
		}


	}
	return result;
}

inline void AutomataSimulator::clear()
{
	m_InputSymbol.clear();
	m_InternalStates.clear();
	m_OutputSymbol.clear();
	m_matrix.clear();
}

void AutomataSimulator::SetSymbolandStates(const std::string& str,int k)
{
	std::vector<std::string>* ptr = (k == 0 ? &m_InputSymbol : k == 1 ? &m_OutputSymbol : k == 2 ? &m_InternalStates : nullptr);
	std::string curentsybol;
	for (const auto& a : str)
	{
		if (a != ',')
		{
			curentsybol.push_back(a);
		}
		else
		{
			(*ptr).push_back(curentsybol);
			curentsybol.clear();
		}
	}
	if (curentsybol.size() > 0)
	{
		(*ptr).push_back(curentsybol);
	}
	/*for (const auto & a:(*ptr))
	{
		std::cout << a << std::endl;
	}*/
}

inline void AutomataSimulator::Setmatrix(const std::string& str)
{
	std::vector<std::pair<char, int>> curent;
	char b = 0;
	std::string q ;
	bool bl = true;

	for (const auto& s : str)
	{
		if (s != '|')
		{
			if (s != ',')
			{
				if (bl)
				{
					b = s;
				}
				else
				{
					q.push_back(s);
				}

			}
			else
			{
				bl = false;
			}
		}
		else
		{
			int index = -1;
			for (int i = 0; i < m_InternalStates.size(); ++i)
			{
				if (q == m_InternalStates.at(i))
				{
					index = i;
					break;
				}
		    }
			if (index != -1)
			{

				curent.push_back(std::pair<char, int>(b, index));
				bl = true;
				q.clear();
				b = 0;
			}
		}
	}
	if (q.size() > 0)
	{
		int index = -1;
		for (int i = 0; i < m_InternalStates.size(); ++i)
		{
			if (q == m_InternalStates.at(i))
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			curent.push_back(std::pair<char, int>(b, index));
			
		}
	}


	this->m_matrix.push_back(curent);
}
