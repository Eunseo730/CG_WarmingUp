using namespace std;
#include <iostream>

// 행렬 다루기

int arr1[4][4];
int arr2[4][4];

int pushCount = 0;

// 두 행렬을 0, 1, 2 중 하나의 수로 초기화
void Init(int arr[4][4])
{
	int count = 0;    // 2의 개수는 2개 이하로만 있어야 함
	int random;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (count >= 2)
			{
				random = rand() % 2;
				arr[j][i] = random;
			}

			else
			{
				random = rand() % 3;
				arr[j][i] = random;

				if (random == 2) count++;
			}
		}
	}
}

void PrintArr(int arr[4][4])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			cout << arr[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// 행렬의 덧셈
void PlusArr(int arr1[4][4], int arr2[4][4])
{
	int temp[4][4];

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			temp[j][i] = arr1[j][i] + arr2[j][i];
		}
	}

	PrintArr(temp);
}

// 행렬의 뺄셈
void MinusArr(int arr1[4][4], int arr2[4][4])
{
	int temp[4][4];

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			temp[j][i] = arr1[j][i] - arr2[j][i];
		}
	}

	PrintArr(temp);
}

// 짝수만 출력
void PrintEven(int arr[4][4])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (arr[j][i] % 2 == 0)
				cout << arr[j][i] << " ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

// 홀수만 출력
void PrintOdd(int arr[4][4])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (arr[j][i] % 2 == 1)
				cout << arr[j][i] << " ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

// 누르는 횟수에 따라 출력
void TrickPrint(int arr1[4][4], int arr2[4][4])
{

	if (pushCount % 3 == 1)
	{
		PrintEven(arr1);
		PrintEven(arr2);

	}

	else if (pushCount % 3 == 2)
	{
		PrintOdd(arr1);
		PrintOdd(arr2);
	}

	else
	{
		PrintArr(arr1);
		PrintArr(arr2);
	}
}

// 입력한 숫자를 행렬에 곱하기
void MultiArr(int num, int arr[4][4])
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			arr[j][i] *= num;
		}
	}
	PrintArr(arr);
}

// 행렬의 곱셈
void MultiArr(int arr1[4][4], int arr2[4][4])
{
	int result[4][4];

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			result[j][i] = 0;

			for (int k = 0; k < 4; k++)
			{
				result[j][i] += arr1[j][k] * arr2[k][i];
			}
		}
	}
	PrintArr(result);
}

// 전치 행렬
void TransArr(int arr[4][4])
{
	int temp[4][4];

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			temp[j][i] = arr[i][j];
		}
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			arr[j][i] = temp[j][i];
		}
	}

	PrintArr(arr);
}

int Det3x3(int arr[3][3])
{
	return arr[0][0] * (arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1])
		- arr[0][1] * (arr[1][0] * arr[2][2] - arr[1][2] * arr[2][0])
		+ arr[0][2] * (arr[1][0] * arr[2][1] - arr[1][1] * arr[2][0]);
}

void Det4x4(int arr[4][4])
{
	int det = 0;
	int sign = 1;

	for (int col = 0; col < 4; col++) {
		// 3x3 소행렬 추출
		int submat[3][3];
		for (int i = 1; i < 4; i++) {
			int subcol = 0;
			for (int j = 0; j < 4; j++) {
				if (j == col) continue;
				submat[i - 1][subcol++] = arr[i][j];
			}
		}

		det += sign * arr[0][col] * Det3x3(submat);
		sign = -sign;
	}

	cout << "값: " << det << endl;
}

// 명령어 입력 받기
void Choose()
{
	char choose;
	cout << "명령어 입력: ";
	cin >> choose;

	if (choose >= '1' && choose <= '9')
	{
		int num = choose - '0';
		MultiArr(num, arr1);
		MultiArr(num, arr2);
	}

	else
	{
		switch (choose)
		{
		case 'm':
			MultiArr(arr1, arr2);
			break;

		case 'a':
			PlusArr(arr1, arr2);
			break;

		case 'd':
			MinusArr(arr1, arr2);
			break;

		case 'r':
			Det4x4(arr1);
			Det4x4(arr2);
			break;

		case 't':
			TransArr(arr1);
			TransArr(arr2);
			break;

		case 'e':
			pushCount++;
			TrickPrint(arr1, arr2);
			break;

		case 's':
			Init(arr1);
			Init(arr2);
			PrintArr(arr1);
			PrintArr(arr2);
			break;

		case 'q':
			exit(0);
			break;

		default:
			cout << "잘못된 명령어 입니다" << endl;
			break;
		}
	}
}

int main()
{
	srand(unsigned(time(NULL)));

	Init(arr1);
	Init(arr2);

	PrintArr(arr1);
	PrintArr(arr2);

	while (true)
	{
		Choose();
	}
}
