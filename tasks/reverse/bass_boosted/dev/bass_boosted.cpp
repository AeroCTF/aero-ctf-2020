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
//local
#include "ARC4.h"

// youtube link = https://www.youtube.com/watch?v=pgB36pPR7s4
// flag = Aero{f9ab233aa72e71a6b688d78035e563673e92a62016baa60efee04ee6ae823f85}

static const std::string flag_hash("11c9e90ed343b8d96d33dda3eb59bdb200c229185000fe1b604d0f76150ce0d2e09b1fae3bf4a0d6ea71c2ae20e0cd31f2233377a5cb2fc32d76d8b6568e32b22c6a7624a525");

constexpr auto MAX_ALIVE_TIME = 15 * 1000; // in miliseconds (10 sec);
const char* enc_link = "\xe9\x66\x55\xa6\xcd\xf3\x0e\x1d\x14\xa3\xb3\x8f\x8d\xfc\xd3\x75\x40\x21\x1b\x7a\x96\x3e\xfc\xcc\x5e\x4c\xa2\x03\x0b\x26\x8b\x39\x80\xfe\x60\xe1\xf4\xb2\xf0\x5a\x26\x1e\xbb";

static const char* banner =
"****************************** BASS BOOSTED *******************************\n"
"***** Enter the correct key and I will give you a link to the new mix *****\n"
"***************************************************************************\n";

class dictionary {
private:
	std::map<char, boost::any> data;
public:
	dictionary()
	{
		data.insert({ 'A', 'z' });
		boost::mt19937 char_rng(13);
		data.insert({ '}', 'L' });

		for (int i = 'a', j = 0; i <= 'f'; i++, j++)
		{
			int val = char_rng();
			val &= 0xff;

			data.insert({ (char)i, val });
		}

		data.insert({ 'r', 'k' });
		boost::rand48 digit_rng(23);
		data.insert({ '{', 'X' });

		for (int i = '0', j = 0; i <= '9'; i++, j++)
		{
			int val = digit_rng();
			val &= 0xff;

			data.insert({ (char)i, val });
		}

		data.insert({ 'o', 's' });
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


class tick_time {
private:
	ULONGLONG value;
public:
	tick_time() { value = GetTickCount64(); };
	ULONGLONG get_value(void) { return value;  };

	ULONGLONG operator - (tick_time const &obj)
	{
		ULONGLONG result;
		result = value - obj.value;
		return result;
	}
};

class flag_alph {
private:
	boost::container::vector<char> data;
public:
	flag_alph() 
	{
		for (int i = 'a'; i <= 'f'; i++)
		{
			data.push_back(i);
		}
		for (int i = '0'; i <= '9'; i++)
		{
			data.push_back(i);
		}
		
		data.push_back('A');
		data.push_back('r');
		data.push_back('o');
		data.push_back('{');
		data.push_back('}');
	};

	bool check_elem(char elem)
	{
		boost::container::vector<char>::iterator it;
		it = boost::find(data, elem);
		
		if (it != data.end())
			return true;
		else
			return false;
	}
};

static std::string t_int("int");
static std::string t_char("char");

static dictionary flag_dict;
static tick_time start_time;
static flag_alph alph;

bool check_dbg_BD(void);
bool check_dbg_tickcount(void);
boost::optional<bool> char_in_scope(char x);
void decrypt_link(std::string UserInput);

int main( int argc, char** argv ) {

	bool is_dbg = check_dbg_BD();
	
	if (is_dbg)
	{
		exit(-1);
	}
	
	std::cout << banner << std::endl;

	std::string UserInput;
	std::cout << "{?} Key: ";
	std::cin >> UserInput;
	
	boost::container::vector<int> input;
	input.reserve(UserInput.size());

	check_dbg_tickcount();

	for (auto i : UserInput)
	{
		boost::optional<bool> check = char_in_scope(i);

		if (check)
			input.push_back((int)i);
		else
			input.push_back(0x0);
	}

	std::reverse(std::begin(input), std::end(input));
	check_dbg_tickcount();

	boost::container::vector<int> _input;
	_input.reserve(input.size());
	
	int seed = 0;

	for (auto i : input)
	{
		boost::any elem = flag_dict.get_elem((char)i);
		const std::type_info& ti = elem.type();
		
		int i_value = 0xfefe;
		char c_value = 0x0;

		std::string elem_type(ti.name());
		check_dbg_tickcount();

		if (elem_type == t_int )
		{
			i_value = boost::any_cast<int> (elem);
			_input.push_back(i ^ i_value);
		}
		else if (elem_type == t_char)
		{
			c_value = boost::any_cast<char> (elem);
			_input.push_back(c_value);
		}
		else
		{
			exit(-1);
		}
		
		check_dbg_tickcount();

		seed += (i_value + c_value);
	}

	boost::mt11213b rnd(seed);
	
	for (int i = 0; i < 10000; i++)
	{
		rnd();
	}

	check_dbg_tickcount();

	boost::lagged_fibonacci607 _rnd(rnd());
	boost::container::vector<int> hashed;

	for (auto i : _input)
	{
		int xor_key = ((int)(_rnd()*100)%100) & 0xff;
		hashed.push_back(xor_key ^ i);
	}
	
	check_dbg_tickcount();

	std::stringstream hashstream;

	for (auto i : hashed)
	{
		hashstream << std::setfill('0') << std::setw(sizeof(char) * 2)
			<< std::hex << i;
	}

	std::string _hash(hashstream.str());

	if (_hash == flag_hash)
	{
		std::cout << "[+] Correct key!" << std::endl;
		decrypt_link(UserInput);
	}
	else
	{
		std::cout << "[-] Incorrect key!" << std::endl;
	}

	return 0;
}

// check BeingDebugged flag
bool check_dbg_BD()
{
	bool res = false;

	__asm {
		mov eax, dword ptr fs : [30h]
		movzx eax, byte ptr[eax + 2]
		mov res, al
	};

	return res;
};

bool check_dbg_tickcount(void)
{
	tick_time now;

	if ((now - start_time) > MAX_ALIVE_TIME)
	{
		exit(-1);
	}
};

boost::optional<bool> char_in_scope(char x)
{
	boost::optional<bool> res;

	if (alph.check_elem(x))
	{
		res = x;
	}

	return res;
};

void decrypt_link(std::string UserInput)
{
	ARC4 rc4;
	rc4.setKey((unsigned char*)(UserInput.c_str()), UserInput.size());
	
	char* out = new char[44];
	memset(out, 0, 44);

	rc4.encrypt((char*)enc_link, out, 44);
	out[43] = '\0';

	std::cout << "This is your link: " << out << std::endl;
}