#include <iostream>
#include <vector>
#include <string>

using namespace std;

// flag - Aero{381a95d003629088c8f1ebc189ab6fe7}

class Encrypt
{
public:
	Encrypt()
	{
		bool ovrfl = false;
		string inp_buf;
		cout << "key: ";

		cin >> inp_buf;

		if ( inp_buf.size() != 16 )
		{
			cout << "[-] Error key size!" << endl;
			exit( -1 );
		}

		for ( auto elem : inp_buf )
		{
			if ( !(( elem >= '0' && elem <= '9' ) ||
				 ( elem >= 'a' && elem <= 'h' ))  
				)
			{
				cout << "[-] Error key!" << endl;
				exit( -1 );
			}
		}

		for ( auto elem : inp_buf )
		{
			key.push_back( (int)elem );
		}

		cout << "text: ";
		string plain;
		cin >> plain;

		// check the size of buffer, size must be less at 64 , else we have overflow and we need to read first 64 chars
		if ( plain.size() > 64 ) 
			ovrfl = true; 

		if ( ovrfl )
		{
			for ( int i = 0 ; i < 64; i++ )
				plaintext.push_back(plain[i]);
		}
		else
		{
			for ( int i = 0 ; i < plain.size(); i++ )
				plaintext.push_back( plain[i] );
		}
	};
	
	~Encrypt(){};
	void show_plaintext()
	{
		for (int i = 0; i < plaintext.size(); i++)
			cout << plaintext[i] << " ";
	};

	void show_key()
	{
		for (int i = 0 ; i < key.size(); i++)
			cout << key[i] << " ";
	};

	void show_table()
	{
		for (int i = 0 ; i < 4; i++){
			for (int j = 0 ; j < 4; j++){
				cout << switch_table[i][j] << " ";
			}
			cout << endl;
		}
	};

	void table_gen() // worked!
	{
		/* key = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
		   table = [ 1, 12, 11, 10,
		   			 2, 13, 16, 9,
		   			 3, 14, 15, 8,
		   			 4,  5,  6, 7 ]
		   	this function generate table from the key
		*/
		int key_index = 0;

		for (int i = 0 ; i < 4; i++){
			switch_table[i][0] = key[key_index];
			key_index++;
		}
		key_index--;
		for (int i = 0 ; i < 4; i++){
			switch_table[3][i] = key[key_index];
			key_index++;
		}
		key_index--;
		for (int i = 3; i >= 0; i--){
			switch_table[i][3] = key[key_index];
			key_index++;
		}
		key_index--;
		for (int i = 3; i >= 1; i--){
			switch_table[0][i] = key[key_index];
			key_index++;
		}

		for (int i = 1; i <= 2; i++){
			switch_table[i][1] = key[key_index];
			key_index++;
		}
		switch_table[2][2] = key[key_index];
		key_index++;
		switch_table[1][2] = key[key_index];
	};

	void gen_enc_key()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				key[4*i+j] = switch_table[i][j];
			}
		}
	};

	void encode() // function of encode plaintext via our key
	{
		for (int i = 0 ; i < plaintext.size(); i++)
		{
			ciphertext.push_back( ( plaintext[ i ] ^ key[ i % 16 ] ) + key[ i % 16 ] );
		}
	};

	void show_ciphertext()
	{
		cout << "Encoded: ";
		for (int i = 0 ; i < ciphertext.size(); i++)
		{
			cout << hex << ciphertext[i];
		}

		cout << endl;
	};

private:
	vector <int> key; // 16 ints digit
	int switch_table[4][4]; // keys perfomance 
	vector<char> plaintext; // 64 chars of plain text 
	vector<int> ciphertext; // 64 chars of encoded text 
};

int main()
{
	int function_num;

	Encrypt cipher; // cipher, key, plaintext init

	cipher.table_gen(); // key init 
	cipher.gen_enc_key();

	cipher.encode();
	cipher.show_ciphertext();

	
	return 0;
}