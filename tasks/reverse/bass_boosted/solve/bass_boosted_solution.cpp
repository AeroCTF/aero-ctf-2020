#include <string>
#include <string.h>
#include <time.h>
#include <vector>
#include <map>
#include <windows.h>
#include <iostream>
#include <winternl.h>
#include <algorithm>
#include <iomanip>

// boost
#include <boost/optional.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/container/vector.hpp>
#include <boost/any.hpp>
#include <boost/random.hpp>

class dictionary {
private:
	std::map<char, boost::any> data;
public:
	dictionary()
	{
		data.insert({ 'z', 'A' });
		boost::mt19937 char_rng(13);
		data.insert({ 'L', '}' });

		for (int i = 'a', j = 0; i <= 'f'; i++, j++)
		{
			std::cout << (char)i << " : " << (char_rng() & 0xff) << std::endl;
		}

		data.insert({ 'k', 'r' });
		boost::rand48 digit_rng(23);
		data.insert({ 'X', '{' });

		for (int i = '0', j = 0; i <= '9'; i++, j++)
		{
			std::cout << (char)i << " : " << (digit_rng() & 0xff) << std::endl;
		}

		data.insert({ 's', 'o' });
	};

	boost::any get_elem(char idx)
	{
		if (data.find(idx) != data.end())
		{
			return data[idx];
		}
		else
		{
			exit(-1);
		}
	};
};

static dictionary flag_dict;

int main()
{
	unsigned char flag_hash[] = "\x11\xc9\xe9\x0e\xd3\x43\xb8\xd9\x6d\x33\xdd\xa3\xeb\x59\xbd\xb2\x00\xc2\x29\x18\x50"
		"\x00\xfe\x1b\x60\x4d\x0f\x76\x15\x0c\xe0\xd2\xe0\x9b\x1f\xae\x3b\xf4\xa0\xd6\xea\x71\xc2\xae\x20\xe0\xcd\x31"
		"\xf2\x23\x33\x77\xa5\xcb\x2f\xc3\x2d\x76\xd8\xb6\x56\x8e\x32\xb2\x2c\x6a\x76\x24\xa5\x25";
	
	unsigned char* result =  new unsigned char[70];

    for (int i = 0xfefe*5; i < (0xfefe+0xff)*70; i++)
    {
		boost::mt11213b rnd(i);

		for (int i = 0; i < 10000; i++)
		{
			rnd();
		}

		boost::lagged_fibonacci607 _rnd(rnd());
			
		memset(result, 0, 70);

		for ( int j = 0; j < 70; j++ )
		{
			int xor_key = ((int)(_rnd() * 100) % 100) & 0xff;
			result[j] = flag_hash[j] ^ xor_key;
		}

		if (result[67] == 'k' && result[66] == 's' && result[65] == 'X' && result[ 69 ] == 'z' )
		{
			break;
		}
    }

	result[70] = '\0';
	result[69] = 'A';
	result[67] = 'r';
	result[66] = 'o';
	result[65] = '{';
	result[0] = '}';

	int char_xor_keys[6] = { 82,176,74,16,230,98 };
	int digit_xor_keys[10] = {83,120,44,212,142,162,35,170,208,219};

	for (int i = 0; i < 6; i++)
	{
		bool match_flag = false;
		int match_val = 0;

		for (int j = 0; j < 70; j++)
		{
			if ((result[j] ^ char_xor_keys[i]) == ('a' + i))
			{
				match_flag = true;
				match_val = result[j];
				break;
			}
		}

		if (match_flag)
		{
			for (int j = 0; j < 70; j++)
			{
				if (result[j] == match_val)
				{
					result[j] = 'a' + i;
				}
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		bool match_flag = false;
		int match_val = 0;

		for (int j = 0; j < 70; j++)
		{
			if ((result[j] ^ digit_xor_keys[i]) == ('0' + i))
			{
				match_flag = true;
				match_val = result[j];
				break;
			}
		}

		if (match_flag)
		{
			for (int j = 0; j < 70; j++)
			{
				if (result[j] == match_val)
				{
					result[j] = '0' + i;
				}
			}
		}
	}
	
	std::string flag((char*)result);
	std::reverse(std::begin(flag), std::end(flag));
	std::cout << flag << std::endl;

}