#include "ArgsParser.h"

//************************************
// Method:    ArgsParser
// FullName:  ArgsParser::ArgsParser
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: int & argc
// Parameter: char * * argv
//************************************
ArgsParser::ArgsParser(int& argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		m_tokens.push_back(std::string(argv[i]));
	}
}

//************************************
// Method:    ~ArgsParser
// FullName:  ArgsParser::~ArgsParser
// Access:    public 
// Returns:   
// Qualifier:
//************************************
ArgsParser::~ArgsParser()
{
}

//************************************
// Method:    GetCmdOption
// FullName:  ArgsParser::GetCmdOption
// Access:    public 
// Returns:   const std::string
// Qualifier: const
// Parameter: const std::string & cmdOption
//************************************
const std::string ArgsParser::GetCmdOption(const std::string& cmdOption) const
{
	vector<string>::const_iterator iterator;
	iterator = find(m_tokens.begin(), m_tokens.end(), cmdOption);

	if (iterator != m_tokens.end() && ++iterator != m_tokens.end())
	{
		return *iterator;
	}

	return "";
}

//************************************
// Method:    CmdOptionExists
// FullName:  ArgsParser::CmdOptionExists
// Access:    public 
// Returns:   bool
// Qualifier: const
// Parameter: const std::string & cmdOption
//************************************
bool ArgsParser::CmdOptionExists(const std::string &cmdOption) const
{
	return find(m_tokens.begin(), m_tokens.end(), cmdOption)
		!= m_tokens.end();
}

