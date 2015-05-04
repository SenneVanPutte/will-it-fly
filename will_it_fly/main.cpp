#include <iostream>

#include <wif_core/wif_core.hpp>
#include <wif_algo/wif_algo.hpp>
#include <wif_viz/wif_viz.hpp>

#include <algorithm>
#include <string>

char * get_cmd_option(char ** _begin,
                      char ** _end,
                      const std::string & option)
{
	char ** itr = std::find(_begin, _end, option);

	if((itr != _end) && (++itr != _end))
		return *itr;

	return 0;
}

bool cmd_option_exists(char ** _begin,
                       char ** _end,
                       const std::string & option)
{
	return std::find(_begin, _end, option) != _end;
}

int main(int argc, char ** argv)
{
	/*
	if(cmd_option_exists(argv, argv + argc, "--help"))
	{
		std::cout << "Will it fly" << std::endl;
		return 0;
	}

	if(cmd_option_exists(argv, argv + argc, "--version"))
	{
		std::cout << "0.0.1" << std::endl;
		return 0;
	}

	std::string foil_filename = get_cmd_option(argv, argv + argc, "--foil");

	if(foil_filename.c_str())
	{
		std::cout << foil_filename.c_str() << std::endl;
		return 0;
	}
	*/

	std::cout << wif_core::get_version() << std::endl;
	std::cout << wif_algo::get_version() << std::endl;
	std::cout << wif_viz::get_version()  << std::endl;
}
