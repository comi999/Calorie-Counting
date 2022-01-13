#pragma once
#include <string>
#include <list>

using namespace std;

namespace Text
{
	bool TryParseInt( const string& a_Text, int& o_Result )
	{
		const char* s = a_Text.c_str();

		if ( s == nullptr || *s == '\0' )
		{
			return false;
		}

		bool Negate = ( s[ 0 ] == '-' );

		if ( *s == '+' || *s == '-' )
		{
			++s;
		}

		if ( *s == '\0' )
		{
			return false;
		}

		int Result = 0;

		while ( *s )
		{
			if ( *s < '0' || *s > '9' )
			{
				return false;
			}

			Result = Result * 10 - ( *s - '0' );
			++s;
		}

		o_Result = Negate ? Result : -Result;
		return true;
	}

	bool TryParseDecimal( const string& a_Text, double& o_Result )
	{
		char* End;
		double Value = strtod( a_Text.c_str(), &End );

		if ( End == a_Text.c_str() )
		{
			return false;
		}

		o_Result = Value;
		return true;
	}

	bool TryParseBool( string a_Text, bool& o_Result )
	{
		for ( char& Char : a_Text )
		{
			Char = tolower( Char );
		}

		if ( a_Text == "t" )
		{
			o_Result = true;
			return true;
		}

		if ( a_Text == "f" )
		{
			o_Result = false;
			return true;
		}

		if ( a_Text == "true" )
		{
			o_Result = true;
			return true;
		}

		if ( a_Text == "false" )
		{
			o_Result = false;
			return true;
		}

		return false;
	}

	template < typename T >
	string ToString( const T& a_Value )
	{
		return to_string( a_Value );
	}

	template <>
	string ToString< bool >( const bool& a_Value )
	{
		return a_Value ? "True" : "False";
	}

	list< string_view > Tokenize( const string& a_Text )
	{
		string Text = a_Text;
		char* Context = nullptr;
		char* token = strtok_s( const_cast< char* >( Text.c_str() ), " '", &Context );
		list< string_view > Result;

		while ( token != nullptr )
		{
			Result.push_back( std::string_view( token ) );
			token = strtok_s( nullptr, " ", &Context );
		}

		return Result;
	}
}