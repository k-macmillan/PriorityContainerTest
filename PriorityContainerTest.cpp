/*
	Simple test to see how containers perform for the application I am working on. 
	Not an all-encompasing test, but a simple demonstration. 
*/

#pragma GCC optimize("-O3")

#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>

using namespace std;

#define RAND rand() % INT_MAX / (rand() % INT_MAX + 0.0)

struct Action
{
	Action() {}
	Action(float Fitness) : fitness(Fitness) {}
	// Other structs
	float fitness;
};

inline bool operator< (const Action& lhs, const Action& rhs) { return lhs.fitness < rhs.fitness; };
bool VecSort(const Action& lhs, const Action& rhs) {return lhs.fitness > rhs.fitness; };

template <class T>
class reservable_priority_queue: public std::priority_queue<T>
{
public:
    typedef typename std::priority_queue<T>::size_type size_type;
    reservable_priority_queue(size_type capacity = 0) { reserve(capacity); };
    void reserve(size_type capacity) { this->c.reserve(capacity); } 
    size_type capacity() const { return this->c.capacity(); } 
};

int main()
{
	unsigned int val;
	srand(42);
	cout << "Enter desired size of containers: ";
	cin >> val;
	cout << endl;


	/////////////////// VECTOR ///////////////////
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	
	// Immediately Invoked Function Expression - slower in this case
	// vector<Action> vec_test;
	// vec_test.reserve(val);
	// for (int i = 0; i < val; ++i)
	// {
		// vec_test.emplace_back([val]()
		// {
			// return RAND;
		// }());
	// }
	
	vector<Action> vec_test;
	vec_test.reserve(val);
	for (unsigned int i = 0; i < val; ++i)
		vec_test.emplace_back(RAND);
	sort(vec_test.begin(), vec_test.end(), VecSort);

	// Vector has a range constructor!
	vector<Action> top_10_v(vec_test.begin(), vec_test.begin() + (val * .1));

	// vector<Action> top_10_v;
	// top_10_v.reserve(val * .1);
	// for (unsigned int i = 0; i < val * .1; ++i)
		// top_10_v.push_back(vec_test[i]);

	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << "Vector time: " << chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << " seconds" << endl;

	// for (unsigned int i = 0; i < 5; ++i)
	// 	cout << vec_test[i].fitness << endl;
	// cout << endl;

	srand(42);


	/////////////////// PRIORITY QUEUE ///////////////////
	chrono::high_resolution_clock::time_point t5 = chrono::high_resolution_clock::now();

	priority_queue<Action> p_queue;

	for (unsigned int i = 0; i < val; ++i)
		p_queue.emplace(RAND);

	priority_queue<Action> top_10_p;

	for (unsigned int i = 0; i < val * .1; ++i)
	{
		top_10_p.push(p_queue.top());
		p_queue.pop();
	}

	chrono::high_resolution_clock::time_point t6 = chrono::high_resolution_clock::now();
	cout << "Priority Queue time: " << chrono::duration_cast<chrono::duration<double>>(t6 - t5).count() << " seconds" << endl;
	// vector<Action> test_vec2;
	// test_vec2.reserve(5);
	// for (unsigned int i = 0; i < 5; ++i)
	// {
	// 	test_vec2.emplace_back(top_10_p.top());
	// 	cout << test_vec2[i].fitness << endl;
	// 	top_10_p.pop();		
	// }
	// cout << endl;

	srand(42);


	/////////////////// RESERVE PRIORITY QUEUE ///////////////////
	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

	reservable_priority_queue<Action> rp_queue;
	rp_queue.reserve(val);

	// priority_queue<Action> p_queue;
	for (unsigned int i = 0; i < val; ++i)
		rp_queue.emplace(RAND);

	reservable_priority_queue<Action> top_10_rp;
	top_10_rp.reserve(val * .1);
	// priority_queue<Action> top_10_p;

	for (unsigned int i = 0; i < val * .1; ++i)
	{
		top_10_rp.push(rp_queue.top());
		rp_queue.pop();
	}

	chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
	cout << "Reserve Priority Queue time: " << chrono::duration_cast<chrono::duration<double>>(t4 - t3).count() << " seconds" << endl;
	// vector<Action> test_vec2;
	// test_vec2.reserve(5);
	// for (unsigned int i = 0; i < 5; ++i)
	// {
	// 	test_vec2.emplace_back(top_10_rp.top());
	// 	cout << test_vec2[i].fitness << endl;
	// 	top_10_rp.pop();		
	// }
	// cout << endl;

	srand(42);


	/////////////////// HEAP ///////////////////
	chrono::high_resolution_clock::time_point t7 = chrono::high_resolution_clock::now();

	vector<Action> heap_vec;
	heap_vec.reserve(val);
	make_heap(heap_vec.begin(), heap_vec.end(), VecSort);
	for (unsigned int i = 0; i < val; ++i)
	{
		heap_vec.emplace_back(RAND);
		push_heap(heap_vec.begin(), heap_vec.end());
	}

	vector<Action> top_10_h;
	top_10_h.reserve(val * .1);
	for (unsigned int i = 0; i < val * .1; ++i)
	{
		top_10_h.push_back(heap_vec.front());
		pop_heap(heap_vec.begin(), heap_vec.end());
		heap_vec.pop_back();
	}

	chrono::high_resolution_clock::time_point t8 = chrono::high_resolution_clock::now();
	cout << "Heap time: " << chrono::duration_cast<chrono::duration<double>>(t8 - t7).count() << " seconds" << endl;
	// for (unsigned int i = 0; i < 5; ++i)
	// 	cout << top_10_h[i].fitness << endl;




	return 0;
}

