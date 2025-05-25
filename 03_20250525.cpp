using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

// 저장 리스트 만들기 (구조체 데이터 사용)

struct Pos
{
	int x;
	int y;
	int z;
};

vector<Pos> lists;

bool IsEmpty(vector<Pos> _list)
{
	int count = 0;

	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].x == 0 && _list[i].y == 0 && _list[i].z == 0)
			count++;
	}

	if (count == _list.size())
	{
		cout << "리스트가 비었음" << endl;
		return true;
	}
	else return false;
}

void PrintList(vector<Pos>& _list)
{
	for (int i = _list.size() - 1; i >=0; i--)
	{
		if (_list[i].x == 0 && _list[i].y == 0 && _list[i].z == 0)
			cout << "Index: " << i << " Pos: " << endl;

		else
		    cout << "Index: " << i << " Pos: " << _list[i].x << _list[i].y << _list[i].z << endl;
	}

	cout << endl;
}

// 리스트의 맨 위에 입력
void InputTop(vector<Pos>& _list)
{
	Pos input;
	cout << "x, y, z를 입력하세요: ";
	cin >> input.x >> input.y >> input.z;

	for (int i = _list.size() - 1; i >= 0; i--)
	{
		if (_list[i].x == 0 && _list[i].y == 0 && _list[i].z == 0)
		{
			_list[i].x = input.x;
			_list[i].y = input.y;
			_list[i].z = input.z;

			break;
		}
	}

	PrintList(_list);
}

// 리스트의 맨 위 삭제
void PopTop(vector<Pos>& _list)
{
	for (int i = _list.size() - 1; i >= 0; i--)
	{
		if (_list[i].x != 0 || _list[i].y != 0 || _list[i].z != 0)
		{
			_list[i].x = 0;
			_list[i].y = 0;
			_list[i].z = 0;

			break;
		}
	}

	PrintList(_list);
}

// 리스트의 가장 아래에 입력
void InputBottom(vector<Pos>& _list)
{
	Pos input;
	cout << "x, y, z를 입력하세요: ";
	cin >> input.x >> input.y >> input.z;

	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].x == 0 && _list[i].y == 0 && _list[i].z == 0)
		{
			_list[i].x = input.x;
			_list[i].y = input.y;
			_list[i].z = input.z;

			break;
		}
	}

	PrintList(_list);
}

// 리스트의 가장 아래 삭제
void PopBottom(vector<Pos>& _list)
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].x != 0 || _list[i].y != 0 || _list[i].z != 0)
		{
			_list[i].x = 0;
			_list[i].y = 0;
			_list[i].z = 0;

			break;
		}
	}
	PrintList(_list);
}

// 리스트에 저장된 점의 개수
void PosCount(vector<Pos> _list)
{
	if (IsEmpty(_list)) return;

	int count = 0;

	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].x != 0 || _list[i].y != 0 || _list[i].z != 0)
		{
			count++;
		}
	}

	cout << count << endl;
}

// 리스트를 비움
void ClearList(vector<Pos>& _list)
{
	if (IsEmpty(_list))
	{
		PrintList(_list);
		return;
	}

	for (int i = 0; i < _list.size(); i++)
	{
		_list[i].x = 0;
		_list[i].y = 0;
		_list[i].z = 0;
	}

	PrintList(_list);
}

// 원점에서 가장 먼 거리에 있는 좌표값 출력
void MaxDistance(vector<Pos> _list)
{
	if (IsEmpty(_list)) return;

	double maxDis = sqrt(_list[0].x * _list[0].x + _list[0].y * _list[0].y + _list[0].z * _list[0].z);
	int index = 0;

	for (int i = 1; i < _list.size(); i++)
	{
		int dis = sqrt(_list[i].x * _list[i].x + _list[i].y * _list[i].y + _list[i].z * _list[i].z);
		if (dis > maxDis)
		{
			maxDis = dis;
			index = i;
		}
	}

	cout << _list[index].x << _list[index].y << _list[index].z << endl;
}

// 원점에서 가장 가까운 거리에 있는 좌표값 출력
void MinDistance(vector<Pos> _list)
{
	if (IsEmpty(_list)) return;

	double minDis = sqrt(_list[0].x * _list[0].x + _list[0].y * _list[0].y + _list[0].z * _list[0].z);
	int index = 0;

	for (int i = 1; i < _list.size(); i++)
	{
		int dis = sqrt(_list[i].x * _list[i].x + _list[i].y * _list[i].y + _list[i].z * _list[i].z);
		if (dis < minDis && (_list[i].x != 0 || _list[i].y != 0 || _list[i].z != 0))
		{
			minDis = dis;
			index = i;
		}
	}

	cout << _list[index].x << _list[index].y << _list[index].z << endl;
}

// 원점과 거리를 정렬해 오름차순으로 정렬해 출력
void UpSort(vector<Pos>& _list)
{
	vector<Pos> temp;
	int index = 0;

	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].x != 0 || _list[i].y != 0 || _list[i].z != 0)
		{
			temp.push_back(_list[i]);
			index++;
		}
	}

	for (int i = 0; i < temp.size() - 1; i++)
	{
		for (int j = 0; j < temp.size() - i - 1; j++)
		{
			if (sqrt(temp[j].x * temp[j].x + temp[j].y * temp[j].y + temp[j].z * temp[j].z)
				> sqrt(temp[j + 1].x * temp[j + 1].x + temp[j + 1].y * temp[j + 1].y + temp[j + 1].z * temp[j + 1].z))
			{
				swap(temp[j], temp[j + 1]);
			}
		}
	}

	temp.resize(_list.size());

	for (int i = index + 1; i < _list.size(); i++)
	{
		temp[i].x = 0;
		temp[i].y = 0;
		temp[i].z = 0;
	}

	PrintList(temp);
}

// 원점과 거리를 정렬해 내림차순으로 정렬해 출력
void DownSort(vector<Pos>& _list)
{
	vector<Pos> temp = _list;

	for (int i = 0; i < _list.size() - 1; i++)
	{
		for (int j = 0; j < _list.size() - i - 1; j++)
		{
			if (sqrt(temp[j].x * temp[j].x + temp[j].y * temp[j].y + temp[j].z * temp[j].z)
				< sqrt(temp[j + 1].x * temp[j + 1].x + temp[j + 1].y * temp[j + 1].y + temp[j + 1].z * temp[j + 1].z))
			{
				swap(temp[j], temp[j + 1]);
			}
		}
	}

	PrintList(temp);
}

void Choose()
{
	char choose;
	cout << "명령어 입력: ";
	cin >> choose;

	switch (choose)
	{
	case '+': InputTop(lists); break;
	case '-': PopTop(lists);  break;
	case 'e': InputBottom(lists); break;
	case 'd': PopBottom(lists); break;
	case 'l': PosCount(lists); break;
	case 'c': ClearList(lists); break;
	case 'm': MaxDistance(lists); break;
	case 'n': MinDistance(lists); break;
	case 'a': UpSort(lists); break;
	case 's': DownSort(lists); break;
	case 'q': exit(0);  break;
	default: cout << "잘못된 명령어" << endl;  break;
	}
}

int main()
{
	lists.reserve(20);
	lists.resize(10);

	PrintList(lists);

	while (true)
		Choose();
}

