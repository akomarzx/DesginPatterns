#include<iostream>
#include<string>

class IPaymentProcessor
{
public:
	virtual void Pay(float Amount)const = 0;
};

class VisaPaymentProcessor : public IPaymentProcessor
{

public:
	void Pay(float Amount) const override
	{
		std::cout << "Paid using Visa! \n";
	}

};

class StripePaymentProcessor : public IPaymentProcessor
{

public:
	void Pay(float Amount) const override
	{
		std::cout << "Paid using Stripe! \n";
	}

};

class Store
{
private:
	IPaymentProcessor* paymentprocessor;
public:
	Store(IPaymentProcessor* processor)
		:paymentprocessor{ processor } {}
	
	void Buy(std::string Customer, float Payment)
	{
		paymentprocessor->Pay(Payment);
	}
	void SwitchPaymentProvider(IPaymentProcessor* PaymentProvider)
	{
		paymentprocessor = PaymentProvider;
	}
};


int main()
{
	IPaymentProcessor* VisaProvider = new VisaPaymentProcessor;
	IPaymentProcessor* StripeProvider = new StripePaymentProcessor;

	Store store(VisaProvider);

	store.Buy("Ronald", 20.0f);
	store.SwitchPaymentProvider(StripeProvider);
	store.Buy("Ronald", 20.0f);
	store.SwitchPaymentProvider(VisaProvider);
	store.Buy("Ronald", 20.0f);



	delete VisaProvider;
	delete StripeProvider;
	return 0;
67}