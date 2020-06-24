
#include <iostream>

#include <vector>

using namespace std;

int main()

{

	void ShuffleCards(vector<int>&cardArray, int k, vector<vector<int> >&outArray, int &t);

	int T, x;

	cin >> T;

	vector<int> xArray;

	int n, k;



	vector<vector<int> >outArray(T);//定义T行的二维数组，不同行可以不等长

	int t = 0;

	while (T--)

	{

		cin >> n >> k;

		vector<int> cardArray(2 * n);//一组牌

		for (int i = 0; i<2 * n; i++)

			cin >> cardArray[i];

		ShuffleCards(cardArray, k, outArray, t);

		t++;

	}

	for (int outi = 0; outi<t; outi++)

	{

		for (vector<int>::const_iterator p = outArray[outi].begin(); p != outArray[outi].end(); p++)

		{

			if (p == outArray[outi].end() - 1)

				cout << *p;

			else

				cout << *p << " ";

		}

		if (outi<t - 1)

			cout << endl;

	}

	return 0;

}

void ShuffleCards(vector<int>&cardArray, int k, vector<vector<int> >&outArray, int&t)

{

	int len = cardArray.size();

	vector<int>a(len);

	while (k--)

	{

		for (int j = len - 1, i = len / 2; j>0; j = j - 2, i--)

		{

			a[j] = cardArray[i + len / 2 - 1];

			a[j - 1] = cardArray[i - 1];



		}

		for (int j = 0; j<len; j++)

			cardArray[j] = a[j];

	}

	outArray[t].resize(len);

	for (int j = 0; j<len; j++)

		outArray[t][j] = cardArray[j];

}
