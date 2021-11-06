// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include<iostream>
#include<vector>
#include<memory>
class Button // Product Interface
{
public:
	virtual void render() = 0;
	virtual void OnClick() = 0;
	virtual ~Button() = default;
};

class WindowsButton : public Button // ConcreteProduct 
{

public:
	void render() override
	{
		std::cout << "Windows button Render!\n";
	}

	void OnClick() override
	{
		std::cout << "Windows Button OnClick\n";
	}
};

class HtmlButton : public Button // ConcreteProduct 2
{

public:
	void render() override
	{
		std::cout << "Html button Render!\n";
	}
	void OnClick() override
	{
		std::cout << "Html button Clicked!\n";

	}

};

class LinuxButton : public Button // ConcreteProduct3
{

public:
	void render() override
	{
		std::cout << "linux button Render!\n";
	}


	void OnClick() override
	{
		std::cout << "Linux Button OnClick\n";
	}

};

class Dialog //Creator Class
{
protected:
	virtual Button* ButtonFactory() = 0;
	Button* ButtonInThisDialog;
public:
	virtual void Render();
	virtual void OnClick();
	virtual ~Dialog()
	{
		delete ButtonInThisDialog;
	}
};

void Dialog::Render()
{
		ButtonInThisDialog = ButtonFactory();
		ButtonInThisDialog->render();
}

void Dialog::OnClick()
{
	ButtonInThisDialog->OnClick();
}

class WindowsDialog : public Dialog
{
protected:
	Button* ButtonFactory() override
	{
		return new WindowsButton;
	}
public:
	void Render()override
	{
		Dialog::Render();
		std::cout << "Making a Windows Dialog\n";
	}
};

class HtmlDialog : public Dialog
{

protected:
	Button* ButtonFactory() override
	{
		return new HtmlButton;
	}
public:
	void Render()override
	{
		Dialog::Render();
		std::cout << "Making html Dialog\n";
	}
};

class LinuxDialog : public Dialog
{

protected:
	Button* ButtonFactory() override
	{
		return new LinuxButton;
	}
public:
	void Render()override
	{
		Dialog::Render();
		std::cout << "Making a linux Dialog\n";
	}
	
};


int main()
{
	
	enum class Platform
	{
		Html = 0,
		Windows = 1,
		Linux = 2
	};
	std::vector<std::unique_ptr<Dialog>> dialogcollections;


	Platform variousPlatforms[]
	{
		Platform::Windows , Platform::Linux , Platform::Linux , Platform::Windows , Platform::Html
	};
	
	for (auto x : variousPlatforms)
	{
		switch (int(x))
		{
		case (int)Platform::Linux:
		{
			dialogcollections.emplace_back(std::make_unique<LinuxDialog>());
			break;
		}
		case (int)Platform::Windows:
		{
			dialogcollections.emplace_back(std::make_unique<WindowsDialog>());
			break;
		}
		case (int)Platform::Html:
		{
			dialogcollections.emplace_back(std::make_unique<HtmlDialog>());
			break;
		}
		default:
		{
			std::cout << "platform Not supported\n";
		}
		}
	}
	
	for (auto &Element : dialogcollections)
	{
		Element->Render();
	}
	for (auto& Element : dialogcollections)
	{
		Element->OnClick();
	}
	
	

	
	return 0;
} 
