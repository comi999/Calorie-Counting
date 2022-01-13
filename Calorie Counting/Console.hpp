#pragma once
#include <iostream>
#include <string>

using namespace std;

namespace Console
{
	void WriteLine( const string& a_Text )
	{
		cout << a_Text << endl;
	}

	void Write( const string& a_Text )
	{
		cout << a_Text;
	}

	string ReadLine()
	{
		string Text;
		getline( cin, Text );
		return Text;
	}

	void Clear()
	{
		system( "cls" );
	}

	void NewLine()
	{
		cout << endl;
	}

	void BackSpace()
	{
		cout << '\b';
	}

	void ClearLine()
	{
		cout << "\x1b[2K";
	}
}