#include "counted_sortedvector.h"
#include <tuple> // for using tie

class A
{
	int x;
	double y;
public:
	A(int x, double y) : x(x), y(y) {}
	bool operator<(const A& a2) const
	{
		/*if (x < a2.x) return true;
		else if (x > a2.x) return false;
		else
		{
			if (y < a2.y) return true;
			else return false;
		}*/
		return tie(x, y) < tie(a2.x, a2.y);
	}
	bool operator==(const A& a2) const
	{
		return (x == a2.x && y == a2.y);
	}
	friend ostream& operator<<(ostream& out, const A& a2);
};
ostream& operator<<(ostream& out, const A& a2) {
	out << "(" << a2.x << ", " << a2.y << ")  ";
	return out;
}

int main()
{
	// Test 2 pass if class give three operator code of "<" ; "==" ; "<<" ;
	counted_sortedvector<A> av1;
	A a1(1, 1.3);
	A a2(4, 4.7);
	A a3(1, 1.3);
	A a4(3, 3.1);
	av1.insert(a1);
	av1.insert(a2);
	av1.insert(a3);
	av1.insert(a4);
	//av.eraseall(a1);
	cout << av1 << endl;
	for (auto& p : av1) {
		cout << "[" << p.first << " x" << p.second << "]  ";
	}
	cout << endl;

	counted_sortedvector<A> av2;
	A a5(2, 2.3);
	A a6(4, 4.7);
	A a7(1, 1.3);
	A a8(3, 3.1);
	av2.insert(a5);
	av2.insert(a6);
	av2.insert(a7);
	av2.insert(a8);

	av2.merge(av1);
	av2.eraseall(a1);
	cout << av2 << endl;
	for (auto& p : av2) {
		cout << "[" << p.first << " x" << p.second << "]  ";
	}
	cout << endl;

	// Test 1 pass
	/*
	counted_sortedvector<int> csv1;
	csv1.insert(5);
	csv1.insert(1);
	csv1.insert(3);
	csv1.insert(9);
	csv1.insert(3);

	cout << "Index of " << 3 << " is " << csv1.findIndex(3) << endl;
	if (csv1.find(3))
		cout << 3 << " Found" << endl;
	else
		cout << 3 << " Not found" << endl;
	cout << "Count of " << 3 << " is " << csv1.count(3) << endl;
	cout << "Print all value: " << endl;
	cout << av << endl;
	cout << "Total size = " << csv1.total_size() << endl;
	cout << "Unique size = " << csv1.unique_size() << endl;

	csv1.erase(1);
	cout << "Print all value (after erase(1)): " << endl;
	cout << av << endl;

	csv1.eraseall(3);
	cout << "Print all value (after eraseall(3)): " << endl;
	cout << av << endl;

	csv1.clear();
	cout << "Print all value (after clear()): " << endl;
	cout << av << endl;
	*/

	return 0;
}