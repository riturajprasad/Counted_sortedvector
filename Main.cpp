#include "counted_sortedvector.h"
#include "count_sortedvector.h"

class A
{
private:
	int x;
	double y;
public:
	A(int x, double y) : x(x), y(y) {}
	void print() const
	{
		cout << x << " & " << y << endl;
	}
	bool operator<(const A& other) const {
		// define your sorting rule
		// return x < other.x;
		return (x == other.x) ? (y < other.y) : (x < other.x);
	}
};

int main()
{
	// Test 2 fail
	/*counted_sortedvector<A> av;
	A a1(1, 2.1);
	A a2(4, 3.5);
	A a3(1, 2.1);
	A a4(3, 2.4);
	av.insert(a1);
	av.insert(a2);
	av.insert(a3);
	av.insert(a4);
	av.printall();*/

	// Test 1 pass
	/*counted_sortedvector<int> csv1;
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
	csv1.printall();
	cout << "Total size = " << csv1.total_size() << endl;
	cout << "Unique size = " << csv1.unique_size() << endl;

	csv1.erase(1);
	cout << "Print all value (after erase(1)): " << endl;
	csv1.printall();

	csv1.eraseall(3);
	cout << "Print all value (after eraseall(3)): " << endl;
	csv1.printall();

	csv1.clear();
	cout << "Print all value (after clear()): " << endl;
	csv1.printall();*/

	return 0;
}