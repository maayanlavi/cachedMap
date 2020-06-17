#include "employee.h"
#include <fstream>
#include <memory>

employee* employee::load(istream& in)
{
		int n = _id.length();
		in.read((char*)&n, sizeof(n));
		in.read((char*)&_id, n);
		in.read((char*)&_salary, sizeof(_salary));
		in.read((char*)&_seniority, sizeof(_seniority));

	
		return this;
		
}

int main()

{
	ifstream inFile;
	inFile.open("emps.bin");
	if (!inFile.is_open())
		cout << "error" << endl;
	
	CachedMap<std::string, employee*>* Cm = new CachedMap<std::string, employee*>();
	while (!(inFile.eof()))
	{
		employee* E=new employee();
		E->load(inFile);
		Cm->add(E->getId(), E);
		std::cout << *(Cm->get(E->getId())) << std::endl;
		
	}
	employee* m = new employee("313374621", 1000000, 5);
	Cm->erase("524206622");
	Cm->add("313374621", m);
	std::cout << *(Cm->get(m->getId())) << std::endl;


}




