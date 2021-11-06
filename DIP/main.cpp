/*
Dependency Inversion Principle:

1. High Level Module should not depend on Lower level modules instead both should depend on Abstractions
2. Abstraction Should not depend on details instead details should depend on abstraction.

*/
#include<iostream>
#include<string>
#include<memory>

class ICalculatorOperation // Abstraction Layer between the Calculator Class and the Operations that A calculator uses
{
public:
	virtual float calculate(float first, float second)const = 0;
};


class AdditionOperation : public ICalculatorOperation // Low level Modules
{

public:
	virtual float calculate(float first, float second) const override
	{
		return (second + first);
	}

};

class SubtractionOperation : public ICalculatorOperation // Low level Modules
{

public:
	virtual float calculate(float first, float second) const override
	{
		return (first - second);
	}

};
class MultiplicationOperation : public ICalculatorOperation
{

public:
	float calculate(float first, float second) const override
	{
		return(first * second);
	}

};


class Calculator // High Level Module
{
public:
	void Solve(float first, float second, ICalculatorOperation* operation)const
	{
		std::cout << operation->calculate(first, second);
	}

};


int main()
{
	Calculator calculator;
	ICalculatorOperation* Addition = new AdditionOperation();
	ICalculatorOperation* Substraction = new SubtractionOperation();
	ICalculatorOperation* Multiply = new MultiplicationOperation();
	calculator.Solve(20.0f, 30.0f, Multiply);


	delete Addition;
	delete Substraction;
	return 0;
}