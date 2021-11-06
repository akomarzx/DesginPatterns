#include<iostream>
#include<string>
#include<vector>
/*
Open Closed Principle states that software modules should be open for extension but closed for modification

We should not edit existing source code that is already tested instead we should be able to extend functionalities by using inheritance.
*/


enum class Size { small, medium, large };
enum class Color { Red, Green, Blue };

struct Product
{
	std::string Name;
	Size size;
	Color color;
};
template<class T>
struct Specificiation
{
	virtual bool IsSatisfied(T* Item) = 0;
};

template<class T>
struct Filter
{
	virtual	std::vector<T*> filter(std::vector<T*> items, Specificiation<T>* Specs) = 0;
};


template<class T>
class ColorSpecification : public Specificiation<Product>
{
private:
	Color color;
public:
	ColorSpecification(Color color)
		:color{ color } {}

	bool IsSatisfied(T* Item) override
	{
		return(Item->color == color);
	}

};

template<class T>
class BetterFilter : public Filter<Product>
{
public:
	std::vector<T*> filter(std::vector<T*> items, Specificiation<Product>* Specs) override
	{
		std::vector<T*> ReturnItem;
		for (auto& Element : items)
		{
			if (Specs->IsSatisfied(Element))
			{
				ReturnItem.push_back(Element);
			}
		}
		return ReturnItem;
	}

};

class SizeSpecification : public Specificiation<Product>
{
	Size size;
public:
	SizeSpecification(Size size)
		:size{ size } {}
	bool IsSatisfied(Product* Item) override
	{
		return(this->size == Item->size);
	}

};

int main()
{
	Product Apple{ "Apple" , Size::medium , Color::Red };
	Product Grapes{ "Grapes" , Size::small , Color::Green };
	Product Guava{ "Guava" , Size::medium , Color::Green };
	std::vector<Product*> items{ &Apple , &Grapes , &Guava };

	BetterFilter<Product> myfilter;
	ColorSpecification<Product> ColorGreen(Color::Green);
	ColorSpecification<Product> RedColor(Color::Red);
	SizeSpecification MediumSpecs(Size::small);
	for (auto element : myfilter.filter(items, &MediumSpecs))
	{
		std::cout << element->Name << '\n';
	}

	std::cout << '\n';

	return 0;
}
