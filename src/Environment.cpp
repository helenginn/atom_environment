// vagabond
// Copyright (C) 2019 Helen Ginn
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
// 
// Please email: vagabond @ hginn.co.uk for more details.

#include "Environment.h"
#include <libsrc/PDBReader.h>
#include <libsrc/Atom.h>
#include <libsrc/Monomer.h>
#include <libsrc/Crystal.h>
#include <hcsrc/FileReader.h>

Environment::Environment()
{
	_tol = 10;
}

void Environment::setPDB(std::string pdb)
{
	PDBReader reader;
	reader.setFilename(pdb);
	_pdb = reader.getCrystal();
}

void Environment::setList(std::string list)
{
	if (!_pdb)
	{
		std::cout << "no pdb" << std::endl;
		return;
	}
	std::cout << "figuring out list " << list << std::endl;
	
	std::vector<std::string> bits = split(list, ',');
	
	for (size_t i = 0; i < bits.size(); i++)
	{
		std::string chain = "";
		std::string num = "";
		
		size_t j;
		for (j = 0; j < bits[i].length(); j++)
		{
			if (bits[i][j] >= 'A' && bits[i][j] <= 'z')
			{
				chain += bits[i][j];
			}
			else
			{
				break;
			}
		}
		
		for (size_t k = j; k < bits[i].length(); k++)
		{
			num += bits[i][k];
		}
		
		int n = atoi(num.c_str());
		AtomList list = _pdb->findAtoms("CA", n, chain);
		
		if (list.size() > 0)
		{
			for (size_t j = 0; j < list.size(); j++)
			{
				std::cout << "Adding " << list[j]->shortDesc() << std::endl;
				_atoms.push_back(list[j]);
			}
		}
	}
	
	std::cout << std::endl;
	std::cout << "Finding atoms near list." << std::endl;
	
	_more = _pdb->getCloseAtoms(_atoms, _tol);
	
	std::map<std::string, int> values;
	
	for (size_t i = 0; i < _more.size(); i++)
	{
		if (_more[i]->isHeteroAtom())
		{
			continue;
		}

		std::string str;
		str += _more[i]->getChainID()[0];
		str += " " + i_to_str(_more[i]->getResidueNum());
		std::string res = _more[i]->getMonomer()->getIdentifier();
		
		if (values[str] > 0)
		{
			continue;
		}

		std::cout << str << " " << res << std::endl;
		values[str] = 1;
//		std::cout << _more[i]->getChainID()[0] << " " <<
//		 _more[i]->shortDesc() << std::endl;
	}
}
