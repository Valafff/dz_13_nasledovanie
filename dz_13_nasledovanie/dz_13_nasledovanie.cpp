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
//��������� ��� ������������ ������


//����� Animal - set, get, voice
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
		cout << "������: " << type << "\t���, ��: "  << weight << "\t";
		setColor(White, Black);
	}

	virtual void voice()
	{
		cout << "����-����";
	}

};

class Cat :public Animal
{
	//����� ��������� ����� ����� ������ ������ �� ���� ����������� �� �������������� ������� protected
	//��� ����,��� ������ ������� ����� �������� �������. ��� ���� ����� ������� �� ������� �������
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
	//������� ���������� ������������� �����, ������� ������ � ������ �� �������� ������, ������������ �������� ������
	Cat(int HP, int weight, Color color, string type) :Animal(type, color, weight)
	{
		//this->type = type;//����� ��������� ��������. ����� � �������� ������ ���� �� �������������� ������� protected
		//this->setType(type);//���� ���� ��������� - �� ��������� � ��� ������ ����� ������

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
		cout << "���" << "\t";
	}
};

class Woolf : public Animal
{
	bool alfa = false;
public:


	void voice() override
	{
		cout << "������";
	}

	void Show()   override
	{
		Animal::Show(); 
		if (alfa)
		{
			cout << "�����" << "\t";
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

//��
//Gyena : Cat

class Gyena : public Cat
{
	string species;

public:	
	Gyena()
	{
		cout << "ctor Cat\n";
		species = "����� ���������";
	}
	Gyena(string species): Cat(6, 20, Brown, "��")
	{
		this->species = species;
	}
	Gyena(string species, int HP, int weight, Color color, string type) :Cat(HP, weight, color, type)
	{
		this->species = species;
	}


	void voice() override
	{
		cout << "�����";
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
		if (type == "����� ����")
		{
			cout << "������������";
		}
		else
		{
			cout << "���-���-���";
		}

	}

	void Show() override
	{
		Woolf::Show();
		if (run)
		{
			cout << "������� ��" << "\t";
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

	Dog(bool run) : Woolf( true, "����� ����", White, 60 )
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

	//Cat obj;//������� ����� ������ ����������� ������� ������, � ����� ����� ������ ����������� �������� ������
	//Cat mycat(7);
	//obj.Show();//��������� � ������ �� �������� ������
	//obj.Animal::Show();//��������� � ������ �������� ������

	vector <shared_ptr<Animal>> Zverinez;

	Zverinez.push_back(make_shared<Cat>(9, 4, Brown, "������� ������"));
	Zverinez.push_back(make_shared<Cat>(5, 2, Red, "������"));
	Zverinez.push_back(make_shared<Cat>(4, 5, Yellow, "��-��"));
	Zverinez.push_back(make_shared<Cat>(2, 100, LightBlue, "����"));

	Zverinez.push_back(make_shared<Woolf>(false, "������", Blue, 300));
	Zverinez.push_back(make_shared<Woolf>(false, "���� �� �������� \"���-��� ��\"", LightMagenta, 40));
	Zverinez.push_back(make_shared<Woolf>(false, "������������� �������", DarkGray, 70));
	Zverinez.push_back(make_shared<Woolf>(true, "������", LightGray, 150));

	Zverinez.push_back(make_shared<Gyena>("����� ���������", 6, 19, Brown, "��"));
	Zverinez.push_back(make_shared<Gyena>("����� ���������", 5, 22, Brown, "������"));
	Zverinez.push_back(make_shared<Gyena>("����� ���������", 4, 21, Brown, "�����"));

	Zverinez.push_back(make_shared<Dog>(true, true, "����� ����", White, 60));
	Zverinez.push_back(make_shared<Dog>(true, false, "����������", White, 45));





		for (auto &var : Zverinez)
	{
		var->Show();
		cout << endl;
		cout << "�����: ";
		var->voice();
		cout << endl;
	}


		//Dog a(true, true, "����� ����", White, 60);
		//a.Show();
}