#pragma once
#include <string>

using namespace std;

struct Macro
{
	Macro( int a_Protein, int a_Fat, int a_Carb )
		: Protein( a_Protein )
		, Fat( a_Fat )
		, Carb( a_Carb )
	{ }

	int GetTotalCalories( int a_TotalGrams ) const
	{
		return 
			GetProteinAsCals( a_TotalGrams ) +
			GetFatAsCals( a_TotalGrams ) +
			GetCarbsAsCals( a_TotalGrams );
	}

	int GetProteinAsCals( int a_TotalGrams ) const
	{
		return ConvertProteinToCal( Protein * a_TotalGrams / 100 );
	}

	int GetFatAsCals( int a_TotalGrams ) const
	{
		return ConvertFatToCal( Fat * a_TotalGrams / 100 );
	}

	int GetCarbsAsCals( int a_TotalGrams ) const
	{
		return ConvertCarbToCal( Carb * a_TotalGrams / 100 );
	}

	int GetProteinInGrams( int a_TotalGrams ) const
	{
		return a_TotalGrams * Protein / 100;
	}

	int GetFatInGrams( int a_TotalGrams ) const
	{
		return a_TotalGrams * Fat / 100;
	}

	int GetCarbInGrams( int a_TotalGrams ) const
	{
		return a_TotalGrams * Carb / 100;
	}

	static inline int ConvertProteinToCal( int a_Grams )
	{
		return 0;
	}

	static inline int ConvertFatToCal( int a_Grams )
	{
		return 0;
	}

	static inline int ConvertCarbToCal( int a_Grams )
	{
		return 0;
	}

	int Protein;
	int Fat;
	int Carb;

};

class Food
{
public:

	Food( string a_Name, Macro a_Macro )
		: m_Name( a_Name )
		, m_Macro( a_Macro )
	{ }

	const string& GetName() const
	{
		return m_Name;
	}

	const Macro& GetMacro() const
	{
		return m_Macro;
	}

private:

	string m_Name;
	Macro m_Macro;

};