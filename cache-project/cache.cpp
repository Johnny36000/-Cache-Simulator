#include "cache.h"


string binary_index(int value, int bits)
{

	bitset<64> result(value);

	return result.to_string().substr(64 - bits);
}
cache::cache(int size1, int line_size1,int cache)
{

	size = size1;
	line_size = line_size1;
	cache_time = cache;
	create_cache();


}
int bin_decimal(string value) 
{
	int result = 0;
	for (int i = value.size(); i >= 0; i--)
	{
		if (value[i] == '1') {

			result += pow(2, value.size() - i - 1);

		}
	}
	return result;
}

cache& cache::getinstance(int size, int line_size,int cache_access)
{

	static cache ca(size, line_size,cache_access);
	
	return ca;
}


void cache::create_cache()
{
	no_blocks = size / line_size;
	offset = log2(line_size);

	
	
	
		index_size = log2(no_blocks);
		
		tag_size = 24 - index_size - offset;
		string temp;
		value val;
		for (int i = 0; i < no_blocks; i++)
		{
			temp = binary_index(i, index_size);
			CA[temp] = val;
		}

	
	
	
}

void cache::move_block(string address)
{

	vector<string> temp; string s1 = "";
	for (int i = 0; i < offset; i++)
	{
		s1 += '0';
	}
	string	block_start = address.substr(0, address.length() - offset) + s1;
	
	
	int b_s = bin_decimal(block_start);
	int b_e = b_s + line_size - 1;
	int block_no = (bin_decimal(address)/no_blocks) % no_blocks;
	string index = binary_index(block_no, index_size);
	while (b_s != b_e) {
		temp.push_back(bitset<24>(b_s).to_string());
		b_s++;
	}
	temp.push_back(bitset<24>(b_e).to_string());
	b_s = bin_decimal(block_start);
	CA[index].data = temp;
	CA[index].valid_bit = 1;
	CA[index].tag = bitset<24>(b_s).to_string().substr(0, tag_size);

	access_times++;
}


void cache::Iprint()
{
	cout << "Memory Access :" << access_times << endl;
	cout << "Hits:" << hit << endl;
	cout << "Miss:" << miss << endl;
	cout << "hit-miss ratio:" << hit / miss << endl;
	cout << "AMAT :" << AMAT() << endl;

	cout << "INDEX|TAG|VALID-BIT|DATA" << endl;
		for (auto it : CA)
		{
			cout << it.first << " |" << it.second.tag << "| " << it.second.valid_bit << " |";
			if (it.second.data.size() != 0)
			{
				for (auto it1 : it.second.data)
				{
					cout << "mem["<<bin_decimal(it1) <<"]" << " ";
					
				}
			}
			cout << endl;
		}
		cout << endl << endl;
}
bool cache::search(string address) 
{
	cahce_entry++;
	string s1 = "";
	for (int i = 0; i < offset; i++)
	{
		s1 += '0';
	}
	
	int block_no = (bin_decimal(address) / no_blocks) % no_blocks;
	string index = binary_index(block_no, index_size);
	
		if (CA[index].tag == address.substr(0, tag_size))
		{
		
			hit++;

			return true;
		}
	
	else
	{
		miss++;
		move_block(address);
		return false;
	}
}

int cache::AMAT()
{ 
	float n1 = (miss / cahce_entry);
	return hit * n1 * (120);
}

