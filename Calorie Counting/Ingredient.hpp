#pragma once
#include "Food.hpp"

class Ingredient
{
public:

	Ingredient( const Food& a_Food, int a_Grams )
		: m_Food( a_Food )
		, m_Grams( a_Grams )
	{ }

	const string& GetName() const
	{
		return m_Food.GetName();
	}

	const Food& GetFood() const
	{
		return m_Food;
	}

	int GetGrams() const
	{
		return m_Grams;
	}

	int GetProteinInGrams() const
	{
		return m_Food.GetMacro().GetProteinInGrams( m_Grams );
	}

	int GetFatInGrams() const
	{
		return m_Food.GetMacro().GetFatInGrams( m_Grams );
	}

	int GetCarbInGrams() const
	{
		return m_Food.GetMacro().GetCarbInGrams( m_Grams );
	}

private:

	Food m_Food;
	int m_Grams;

};