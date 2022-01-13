#pragma once
#include "Ingredient.hpp"
#include "Recipe.hpp"
#include "SearchGraph.hpp"

using namespace std;

class FoodDatabase
{
public:

	void InsertFood( const Food& a_Food )
	{
		m_Food.emplace( a_Food.GetName(), a_Food );
		m_FoodSearch.Insert( a_Food.GetName(), a_Food );
	}

	void InsertRecipe( const Recipe& a_Recipe )
	{
		m_Recipe.emplace( a_Recipe.GetName(), a_Recipe );
		InsertFood( a_Recipe.AsFood() );
		m_RecipeSearch.Insert( a_Recipe.GetName(), a_Recipe );
	}

	Food* GetFood( string a_Name )
	{
		auto Result = m_Food.find( a_Name );

		if ( Result == m_Food.end() )
		{
			return nullptr;
		}

		return &Result->second;
	}

	Recipe* GetRecipe( string a_Name )
	{
		auto Result = m_Recipe.find( a_Name );

		if ( Result == m_Recipe.end() )
		{
			return nullptr;
		}

		return &Result->second;
	}

	list< Food* > SearchFood( string a_Name )
	{
		return m_FoodSearch.Search( a_Name );
	}

	list< Recipe* > SearchRecipe( string a_Name )
	{
		return m_RecipeSearch.Search( a_Name );
	}

	Food* FindFood( string a_Name )
	{
		auto& Result = m_FoodSearch.Match( a_Name );
		return Result.size() == 0 ? nullptr : &Result[ 0 ];
	}

	Recipe* FindRecipe( string a_Name )
	{
		auto& Result = m_RecipeSearch.Match( a_Name );
		return Result.size() == 0 ? nullptr : &Result[ 0 ];
	}

private:

	SearchGraph< Food > m_FoodSearch;
	SearchGraph< Recipe > m_RecipeSearch;
	map< string, Food > m_Food;
	map< string, Recipe > m_Recipe;

};