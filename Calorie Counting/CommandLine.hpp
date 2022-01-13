#pragma once
#include <map>
#include <string_view>
#include "Delegate.hpp"
#include "Text.hpp"
#include "Console.hpp"

// Commands should be structured like command1 command2 arg1 arg2 arg3 command3
// Args should be surrounded with "" marks.
// Examples:
// goto Shop1
// set macro food "cheesecake" 30 20 50
// get macro food "cheesecake"
// get calories food "cheesecake"
// get calories food protein "cheesecake"

using namespace std;

struct Keyword
{
	string Value;
};

struct Argument
{
	enum class Type
	{
		Int,
		Float,
		Bool,
		String
	};

	Argument( const string& a_Argument )
		: m_Argument( a_Argument )
		, m_Type( Type::String )
	{
		if ( a_Argument.front() == '"' && a_Argument.back() == '"' )
		{
			m_Type == Type::String;
			m_Value.String = string_view( m_Argument.c_str() + 1, m_Argument.size() - 2 );
			return;
		}

		if ( Text::TryParseBool( a_Argument, m_Value.Bool ) )
		{
			m_Type = Type::Bool;
			return;
		}

		if ( Text::TryParseInt( a_Argument, m_Value.Int ) )
		{
			m_Type = Type::Int;
			return;
		}

		double Decimal;

		if ( Text::TryParseDecimal( a_Argument, Decimal ) )
		{
			m_Type = Type::Float;
			m_Value.Float = Decimal;
			return;
		}

		m_Value.String = m_Argument;
	}

	int GetInt() const
	{
		return m_Value.Int;
	}

	float GetFloat() const
	{
		return m_Value.Float;
	}

	bool GetBool() const
	{
		return m_Value.Bool;
	}

	const string_view GetString() const
	{
		return m_Value.String;
	}

private:

	union Underlying
	{
		int			Int;
		float		Float;
		bool		Bool;
		string_view String;
		Underlying() : Int( 0 ) { }
		~Underlying() { }
	}      m_Value;
	string m_Argument;
	Type   m_Type;
	
};

struct Command
{
	Command( const string& a_Input )
	{
		list< string_view > Output = Text::Tokenize( a_Input );
		list< string_view > Result;
		bool Quotation = false;
		size_t Tail = 0;

		for ( string_view& View : Output )
		{
			if ( View.front() == 39 && !Quotation )
			{
				Quotation = true;
				Tail = View.data() - a_Input.c_str();
			}
			else if ( View.back() == 39 && Quotation )
			{
				Quotation = false;
				size_t Head = View.data() - a_Input.c_str();
				string_view View = a_Input;
				Result.push_back( View.substr( Tail, Head - Tail + 1 ) );
			}
			else
			{
				Result.push_back( View );
			}
		}

		for ( string_view& View : Result )
		{
			Words.emplace_back( View );
		}
	}

	list< string > Words;
};

class CommandGraph
{
	struct Node
	{
		Node( const string& a_Keyword )
			: Keyword( a_Keyword )
		{ }

		void RegisterCommand( const Action< const list< string >& >& a_Action )
		{
			Actions.Add( a_Action );
		}

		void RegisterCommand( const Action< const list< string >& >& a_Action, const list< string >& a_Keywords, int a_Index )
		{
			
		}

		string Keyword;
		map< string, Node* > SubCommands;
		Delegate< void, const list< string >& > Actions;
	};

	Node* FindNode( const string& a_CommandString )
	{

	}

private:

	Node* m_CurrentNode;

};

class CommandLine
{

};