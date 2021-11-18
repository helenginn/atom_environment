#include <cstdlib>
#include <iostream>
#include "commit.h"
#include "Environment.h"

int main(int argc, char * argv[])
{
	std::string pdb, list;
	double tol = 10;
	
	if (argc == 1)
	{
		std::cout << "Usage: " << std::endl;
		std::cout << argv[0] << " ";
		std::cout << "[max distance] [pdb file] [atom_list]" << std::endl;
		std::cout << std::endl;
		std::cout << "max distance in Angstroms" << std::endl;
		std::cout << "pdb file [xxx.pdb]" << std::endl;
		std::cout << "atom list, e.g. E501,E446" << std::endl;
		exit(0);
	}
	
	if (argc > 1)
	{
		tol = atof(argv[1]);
	}

	if (argc > 2)
	{
		pdb = std::string(argv[2]);
	}
	
	Environment env;
	env.setTolerance(tol);

	try
	{
		env.setPDB(pdb);
	}
	catch (int e)
	{
		std::cout << "Failed to set PDB for environment." << std::endl;
		exit(1);
	}

	if (argc > 3)
	{
		list = std::string(argv[3]);
	}
	
	env.setList(list);

	return 0;
}
