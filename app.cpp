#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <iterator>
#include <string>

using namespace std;

unordered_map<int, int> counter;

struct esca_sort
{
	bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const
	{
		return lhs.second < rhs.second;
	}
};

map<pair<int, int>, pair<bool, bool>, esca_sort> e_refstr;

struct ez_cmp
{
	bool operator()(int const &lhs, int const &rhs) const
	{
		return counter[lhs] < counter[rhs];
	}
};

int fifo(vector<int> *refstr, unsigned int *frame_count)
{
	unordered_set<int> frames;

	int changes = 0;
	int start_index = 0;

	for (vector<int>::iterator i = refstr->begin(); i != refstr->end(); i++)
	{
		if (frames.find(*i) == frames.end()) //Not found
		{
			frames.insert(*i);
			changes++;
			while (frames.size() > *frame_count)
				if (frames.find(refstr->at(start_index++)) != frames.end())
					frames.erase(frames.find(refstr->at(start_index - 1)));
		}
	}

	return changes;
}

int lru(vector<int> *refstr, unsigned int *frame_count)
{
	counter.clear();
	int changes = 0;
	for (vector<int>::iterator i = refstr->begin(); i != refstr->end(); i++)
	{
		if (!counter[*i])
			changes++;
		counter[*i]++;
		if ((unsigned int)distance(refstr->begin(), i) >= *frame_count)
			counter[*(i - *frame_count)]--;
	}
	return changes;
}

int lfu(vector<int> *refstr, unsigned int *frame_count)
{

	counter.clear();
	set<int, ez_cmp> frames;
	int changes = 0;

	for (vector<int>::iterator i = refstr->begin(); i != refstr->end(); i++)
	{
		counter[*i]++;

		if (frames.find(*i) == frames.end())
		{
			if (frames.size() == *frame_count)
				frames.erase(frames.begin());
			frames.insert(*i);
			changes++;
		}
		else
		{
			frames.erase(frames.find(*i));
			frames.insert(*i);
		}

		counter[*i]++;
	}

	return changes;
}

int sca(vector<int> *refstr, unsigned int *frame_count)
{
	return lru(refstr, frame_count);
}

int esca(vector<int> *refstr, unsigned int *frame_count)
{
	set<pair<int, int>, esca_sort> frames00;
	set<pair<int, int>, esca_sort> frames01;
	set<pair<int, int>, esca_sort> frames10;
	set<pair<int, int>, esca_sort> frames11;
	unordered_set<int> frames;
	int changes = 0;

	for (unsigned int i = 0; i < refstr->size(); i++)
		e_refstr.insert(e_refstr.end(), make_pair(pair<int, int>(refstr->at(i), i + 1), pair<bool, bool>(true, rand() % 2)));

	for (auto &ref : e_refstr)
	{
		if (frames.find(ref.first.first) == frames.end())
		{
			if (frames.size() == *frame_count)
			{

			Finding_Target:

				if (frames00.size())
				{
					frames.erase(frames.find((*frames00.begin()).first));
					frames00.erase(frames00.begin());
				}
				else if (frames01.size())
				{
					frames.erase(frames.find((*frames01.begin()).first));
					frames01.erase(frames01.begin());
				}
				else
				{
					if (frames10.size())
						for (auto &ele : frames10)
						{
							frames00.insert(ele);
							e_refstr[ele].first = false;
						}
					if (frames11.size())
						for (auto &ele : frames11)
						{
							frames01.insert(ele);
							e_refstr[ele].first = false;
						}

					frames10.clear();
					frames11.clear();

					goto Finding_Target;
				}
			}
			frames.insert(ref.first.first);
			if (ref.second.second)
				frames11.insert(ref.first);
			else
				frames10.insert(ref.first);

			changes++;
		}
		else
		{
			if (!e_refstr[ref.first].first)
			{
				if (e_refstr[ref.first].second)
				{
					frames01.erase(frames01.find(ref.first));
					frames11.insert(ref.first);
				}
				else
				{
					frames00.erase(frames01.find(ref.first));
					frames10.insert(ref.first);
				}
				e_refstr[ref.first].first = true;
			}
		}
	}

	return changes;
}

int optimal(vector<int> *refstr, unsigned int *frame_count)
{
	unordered_set<int> frames;

	int changes = 0;
	for (vector<int>::iterator i = refstr->begin(); i != refstr->end(); i++)
	{
		if (frames.find(*i) == frames.end())
		{
			if (frames.size() == *frame_count)
			{

				bool replaced = false;
				unordered_set<int> found_pages;
				for (vector<int>::iterator j = i + 1; j != refstr->end(); j++)
				{
					if (frames.find(*j) != frames.end() && found_pages.find(*j) == found_pages.end())
					{
						found_pages.insert(*j);

						if (found_pages.size() == frames.size())
						{
							frames.erase(frames.find(*j));
							frames.insert(*i);
							replaced = true;
							break;
						}
					}
				}

				if (!replaced)
				{
					for (unordered_set<int>::iterator j = frames.begin(); j != frames.end(); j++)
					{
						if (found_pages.find(*j) == found_pages.end())
						{
							frames.erase(j);
							frames.insert(*i);
							break;
						}
					}
				}
			}

			else
				frames.insert(*i);

			changes++;
		}
	}

	return changes;
}

int main(int argc, char *argv[])
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	if (argc < 3)
	{
		cout << "2 Arguments (Length of the Reference String, Number of Page Frames) are needed for the program to execute." << endl;
		return 0;
	}
	unsigned int ref_len = stoi(argv[1]),
		frame_count = stoi(argv[2]);

	vector<int> ref_str;

	for (unsigned int i = 0; i < ref_len; i++)
		ref_str.push_back(rand() % 100);

	cout << fifo(&ref_str, &frame_count) << " "
		<< lru(&ref_str, &frame_count) << " "
		<< lfu(&ref_str, &frame_count) << " "
		<< sca(&ref_str, &frame_count) << " "
		<< esca(&ref_str, &frame_count) << " "
		<< optimal(&ref_str, &frame_count);

	return 0;
}

