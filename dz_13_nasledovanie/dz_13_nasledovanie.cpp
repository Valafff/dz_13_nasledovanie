#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <io.h>
#include <algorithm>
#include <vector>
//#include  <memory>


using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}
//прочитать про наследование Ромбом


//класс Animal - set, get, voice
//Cat : Animal - set, get,
//Woolf : Animal  



class Animal
{
protected:
	string type;
	Color color;
	int weight;
public:

	void setType(string type)
	{
		this->type = type;
	}
	void setcolor(Color color)
	{
		this->color = color;
	}
	void setWeight(int weight)
	{
		this->weight = weight;
	}
	string getType() const
	{
		return type;
	}

	Color getColor() const
	{
		return color;
	}

	int getWeight() const
	{
		return weight;
	}

	Animal()
	{
		cout << "ctor Animal\n";
		type = "Animal";

		color = White;
		weight = 1;
	}
	Animal(string type, Color color, int weight)
	{
		cout << "ctor Animal all args\n";
		this->type = type;
		this->color = color;
		this->weight = weight;
	}

	virtual	void Show()
	{
		setColor(color, Black);
		cout << "Объект: " << type << "\tВес, кг: "  << weight << "\t";
		setColor(White, Black);
	}

	virtual void voice()
	{
		cout << "Буль-Буль";
	}

};

class Cat :public Animal
{
	//класс наследник будет иметь прямой доступ ко всем компонентам со спецификатором доступа protected
	//при этом,для любого другого места создания объекта. эти поля будут закрыты от прямого доступа
	int HP = 9;
public:

	void setHp(int HP)
	{
		//if
		this->HP = HP;
	}

	int getHP() const
	{
		return HP;
	}

	Cat()
	{
		cout << "ctor Cat\n";
		HP = 9;
	}
	Cat(int HP) :Animal("Cat", Yellow, 2)
	{
		this->HP = HP;
		cout << "ctor Cat HP\n";
	}
	//передаём управление инициализацей полей, которые пришли в котика из базового класса, конструктору базового класса
	Cat(int HP, int weight, Color color, string type) :Animal(type, color, weight)
	{
		//this->type = type;//такое обращение возможно. еесли у базового класса поля со спецификатором доступа protected
		//this->setType(type);//если поля приватные - то обращение к ним только через методы

		this->HP = HP;
		cout << "ctor Cat all\n";
	}
	void Show() override
	{
		Animal::Show();
		cout << "HP = " << HP << "\t";
	}

	void voice() override
	{
		cout << "Мяу" << "\t";
	}
};

class Woolf : public Animal
{
	bool alfa = false;
public:


	void voice() override
	{
		cout << "Уууууу";
	}

	void Show()   override
	{
		Animal::Show(); 
		if (alfa)
		{
			cout << "Вожак" << "\t";
		}
	}

	Woolf()
	{
		cout << "ctor woolf";
		alfa = true;
	}

	Woolf(bool alfa) : Animal("Alfavish", Red, 85)
	{
		this->alfa = alfa;
	}

	Woolf(bool alfa, string type, Color color, int weight) :Animal(type, color, weight)
	{
		this->alfa = alfa;
	}
};

//ДЗ
//Gyena : Cat

class Gyena : public Cat
{
	string species;

public:	
	Gyena()
	{
		cout << "ctor Cat\n";
		species = "Гиена пятнистая";
	}
	Gyena(string species): Cat(6, 20, Brown, "Эд")
	{
		this->species = species;
	}
	Gyena(string species, int HP, int weight, Color color, string type) :Cat(HP, weight, color, type)
	{
		this->species = species;
	}


	void voice() override
	{
		cout << "МИАуу";
	}

	void Show() override
	{
		Cat::Show();
		cout << "\t" << species;
	}
	string getspecies()
	{
		return species;
	}


};

//Dog : Woolf
class Dog : public Woolf
{
	bool run = true;

public: 
	void voice() override
	{
		if (type == "Белый клык")
		{
			cout << "УУУууууууууу";
		}
		else
		{
			cout << "Гав-Гав-Гав";
		}

	}

	void Show() override
	{
		Woolf::Show();
		if (run)
		{
			cout << "Ездовой пёс" << "\t";
		}
	}
	bool getRun()
	{
		return run;
	}

	Dog()
	{
		cout << "ctor woolf";
		run = false;
	}

	Dog(bool run) : Woolf( true, "Белый клык", White, 60 )
	{
		this->run = run;
	}

	Dog(bool run, bool d_alfa, string type, Color color, int weight) :Woolf(d_alfa, type, color, weight)
	{
		this->run = run;
	}

};

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	//Cat obj;//сначала будет вызван конструктор базовго класса, а потом будет вызван конструктор текущего класса
	//Cat mycat(7);
	//obj.Show();//обращение к методу из текущего класса
	//obj.Animal::Show();//обращение к методу базового класса

	vector <shared_ptr<Animal>> Zverinez;

	Zverinez.push_back(make_shared<Cat>(9, 4, Brown, "Бернард Юджиан"));
	Zverinez.push_back(make_shared<Cat>(5, 2, Red, "Мурзик"));
	Zverinez.push_back(make_shared<Cat>(4, 5, Yellow, "Ми-Ми"));
	Zverinez.push_back(make_shared<Cat>(2, 100, LightBlue, "Сомс"));

	Zverinez.push_back(make_shared<Woolf>(false, "Фенрир", Blue, 300));
	Zverinez.push_back(make_shared<Woolf>(false, "Волк из мультика \"Жил-был пёс\"", LightMagenta, 40));
	Zverinez.push_back(make_shared<Woolf>(false, "Капитолийская волчица", DarkGray, 70));
	Zverinez.push_back(make_shared<Woolf>(true, "Акелла", LightGray, 150));

	Zverinez.push_back(make_shared<Gyena>("Гиена пятнистая", 6, 19, Brown, "Эд"));
	Zverinez.push_back(make_shared<Gyena>("Гиена пятнистая", 5, 22, Brown, "Банзай"));
	Zverinez.push_back(make_shared<Gyena>("Гиена пятнистая", 4, 21, Brown, "Шензи"));

	Zverinez.push_back(make_shared<Dog>(true, true, "Белый клык", White, 60));
	Zverinez.push_back(make_shared<Dog>(true, false, "Одноглазый", White, 45));





		for (auto &var : Zverinez)
	{
		var->Show();
		cout << endl;
		cout << "Голос: ";
		var->voice();
		cout << endl;
	}


		//Dog a(true, true, "Белый клык", White, 60);
		//a.Show();
}