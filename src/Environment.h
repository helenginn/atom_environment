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

#ifndef __vagabond__Environment__
#define __vagabond__Environment__

#include <string>
#include <libsrc/shared_ptrs.h>

class Environment
{
public:
	Environment();

	void setPDB(std::string pdb);
	void setList(std::string list);
	void setTolerance(double tol)
	{
		_tol = tol;
	}
private:
	AtomList _atoms;
	AtomList _more;
	CrystalPtr _pdb;

	double _tol;
};

#endif
