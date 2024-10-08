#ifndef DICTIONARY_H
# define DICTIONARY_H

# include <string>
# include <map>
# include <set>
# include <vector>

class Dictionary
{
	private:
		std::map<std::string, std::string> contentTypes;
		std::set<std::string> methods;
		void _setContentTypes();
		void _setMethods();
	public:
		Dictionary();
		~Dictionary();
		void init();
		bool	isMethodInDictionary(std::string method);
		std::string	getContentTypeFromDictionary(std::string type);
};



#endif
