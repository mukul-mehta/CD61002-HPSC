#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<math.h>

using namespace std;

int main()
{
	int ans = 1;
	while (ans != 0)
	{
		int i, j;
		double l = 0;
		const int n = 6;
		double a[n][n], b[n][1], x[n][1], T[n][1], e, k, I[n][4], IOFF[1][4];
		int tempe;

		for (int i = 0; i < n; i++)
		{
			cout << "Enter b [" << i << "]";
			cin >> b[i][0];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << "DIAG [" << i << "][" << j << " ";
				cin >> I[i][j];
			}
		}
		for (int i = 0; i < 4; i++)
		{
			cout << "Enter IOFF [" << i << "]";
			cin >> IOFF[0][i];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				a[i][j] = 0;
			}
		}

		cout << "Enter the Accuracy = ";
		cin >> e;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 4; j++)
			{	
				tempe = IOFF[0][j];
				if (I[i][j] == 1000)
					continue;
				a[i][i+tempe] = I[i][j];
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << "a[" << i << "][" << j << "]" << "=" << a[i][j] << "  ";
			}
			cout << "\n";
		}

		for (i = 0; i < n; i++)
			T[i][0] = 0;
		l = 0;
		while (1)
		{	
			l = 0;
			cout << "\nIteration no: " << l << "\n";
			for (i = 0; i < n; i++)
			{
				x[i][0] = (1 / a[i][i])*(b[i][0]);
				for (j = 0; j < n; j++)
				{
					if (j != i)
						x[i][0] = x[i][0] - (1 / a[i][i])*(a[i][j] * T[j][0]);
					//cout << x[i][0] << " ";
				}
				//cout << "\n";
			}
			for (i = 0; i < n; i++)
			{
				if (fabs(x[i][0] - T[i][0]) < e);
				l++;
			}
			if (l >= n)
				break;
			for (i = 0; i < n; i++)
				T[i][0] = x[i][0];

			/*for (i = 0; i < n; i++)
				cout << "x" << i + 1 << "=" << x[i][0] << endl;*/
		};
		for (i = 0; i < n; i++)
			cout << "x" << i + 1 << "=" << x[i][0] << endl;

	};
	_getch();
	return 0;
}

