#pragma once
#include <string>
#include <vector>
#include <list>
#include <queue>

using namespace std;

template < typename T >
class SearchGraph
{
	struct Node
	{
		Node( char a_Char )
			: Char( a_Char )
		{
			for ( int i = 0; i < 26; ++i )
			{
				Nodes[ i ] = nullptr;
			}
		}

		T* Insert( const char* a_Name, const T& a_Value )
		{
			if ( *a_Name == '\0' )
			{
				Values.push_back( a_Value );
				return &Values.back();
			}

			auto ConvertToLower = []( char a_Char )
			{
				if ( a_Char >= 'A' && a_Char <= 'Z' )
				{
					a_Char = a_Char + 'a' - 'A';
				}

				return a_Char;
			};

			char Lower = ConvertToLower( *a_Name );
			Node*& SubNode = Nodes[ Lower - 'a' ];

			if ( !SubNode )
			{
				SubNode = new Node( Lower );
			}

			return SubNode->Insert( a_Name + 1, a_Value );
		}

		Node* Search( const char* a_Name )
		{
			if ( *a_Name == '\0' )
			{
				return this;
			}

			auto ConvertToLower = []( char a_Char )
			{
				if ( a_Char >= 'A' && a_Char <= 'Z' )
				{
					a_Char = a_Char + 'a' - 'A';
				}

				return a_Char;
			};

			char Lower = ConvertToLower( *a_Name );
			Node*& SubNode = Nodes[ Lower - 'a' ];

			if ( SubNode == nullptr )
			{
				return nullptr;
			}
			
			return SubNode->Search( a_Name + 1 );
		}

		list< T* > GetAllValues()
		{
			list< T* > Result;
			
			for ( T& Value : Values )
			{
				Result.push_back( &Value );
			}
			
			for ( int i = 0; i < 26; ++i )
			{
				if ( Nodes[ i ] != nullptr )
				{
					Result.merge( Nodes[ i ]->GetAllValues() );
				}
			}

			return Result;
		}

		char Char;
		Node* Nodes[ 26 ];
		vector< T > Values;
	};

public:

	SearchGraph()
		: m_Root( 0 )
	{ }

	T* Insert( string a_Key, const T& a_Value )
	{
		const char* String = a_Key.c_str();
		return m_Root.Insert( String, a_Value );
	}

	list< T* > Search( string a_Key )
	{
		if ( a_Key == "" )
		{
			return m_Root.GetAllValues();
		}

		const char* String = a_Key.c_str();

		Node* FoundNode = m_Root.Search( String );
		
		if ( !FoundNode )
		{
			return list< T* >();
		}

		return FoundNode->GetAllValues();
	}

	vector< T >& Match( string a_Key )
	{
		static vector< T > Empty;

		Node* FoundNode = m_Root.Search( a_Key.c_str() );

		if ( !FoundNode )
		{
			return Empty;
		}

		return FoundNode->Values;
	}

private:

	Node m_Root;

};