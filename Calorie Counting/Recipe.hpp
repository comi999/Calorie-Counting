#pragma once
#include <string>
#include <map>

#include "Ingredient.hpp"

using namespace std;

class Recipe
{
public:

	Recipe( string a_Name )
		: m_Name( a_Name )
	{ }

	const string& GetName() const
	{
		return m_Name;
	}

	void PushIngredient( const Ingredient& a_Ingredient )
	{
		m_Ingredients.emplace( make_pair( a_Ingredient.GetFood().GetName(), a_Ingredient ) );
	}

	Food AsFood() const
	{
		int Protein = 0;
		int Fat = 0;
		int Carb = 0;

		for ( auto& IngredientPair : m_Ingredients )
		{
			Protein += IngredientPair.second.GetFood().GetMacro().Protein;
			Fat += IngredientPair.second.GetFood().GetMacro().Fat;
			Carb += IngredientPair.second.GetFood().GetMacro().Carb;
		}

		Protein /= m_Ingredients.size();
		Fat /= m_Ingredients.size();
		Carb /= m_Ingredients.size();

		return Food( m_Name, Macro( Protein, Fat, Carb ) );
	}

	Ingredient AsIngredient() const
	{
		int Protein = 0;
		int Fat = 0;
		int Carb = 0;
		int Grams = 0;

		for ( auto& IngredientPair : m_Ingredients )
		{
			Protein += IngredientPair.second.GetFood().GetMacro().Protein;
			Fat += IngredientPair.second.GetFood().GetMacro().Fat;
			Carb += IngredientPair.second.GetFood().GetMacro().Carb;
			Grams += IngredientPair.second.GetGrams();
		}

		Protein /= m_Ingredients.size();
		Fat /= m_Ingredients.size();
		Carb /= m_Ingredients.size();

		return Ingredient( Food( m_Name, Macro( Protein, Fat, Carb ) ), Grams );
	}

private:

	string m_Name;
	map< string, Ingredient > m_Ingredients;

};