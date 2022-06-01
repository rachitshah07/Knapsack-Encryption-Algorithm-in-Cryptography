#include <bits/stdc++.h>
using namespace std;
bool Backtracking(int a[], int n, int sum, string &s)
{
    if (sum == 0)
        return true;
    if (n == 0)
        return false;
    if (a[n - 1] > sum)
    {
        return Backtracking(a, n - 1, sum, s);
    }
    else
    {
        bool flag = false;
        flag = Backtracking(a, n - 1, sum, s);
        if (flag)
            return true;
        s[n - 1] = '1';
        flag = Backtracking(a, n - 1, sum - a[n - 1], s);
        if (!flag)
        {
            s[n - 1] = '0';
        }
        return flag;
    }
    s[n - 1] = '0';
    return false;
}
// 1 2 3 4 5--> 7 -> 1+2+4 , 4+3,5+2
bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
int modInverse(int a, int m)
{
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return 0;
}

int main()
{
    cout << "\t\t\t*****************************************" << endl;
    cout << "\t\t\tKNAPSACK-ENCRYPTION-DECRYPTION-ALGORTITHM" << endl;
    cout << "\t\t\t*****************************************" << endl;
    srand(time(0));
    string s;
    cout << "\n\n";
    cout << "\t\t\tENTER THE STRING in Binary:\n\t\t\t\t";
    cin >> s;
    int Private_Key[6], incrementing_zeroes = 6 - (s.size() % 6); // 3
    int incrementing_zeroes_2 = incrementing_zeroes;              // 5
    int x = 1, y = 10, increasing_sum = 0;
    if (incrementing_zeroes < 6)
    {
        while (incrementing_zeroes--)
            s = '0' + s;
    }
    cout << "\n\t\t\tString characters in MULTIPLE of SIX: \n\t\t\t\t";
    cout << s << endl;
    // x -> lower limit
    // y-> upper limit
    // number b/w x and y

    // PRIVATE KEY
    cout << "\n\t\t******************************************************************" << endl;
    cout << "\t\tPrivate key:\t\t\t\t";
    for (int i = 0; i < 6; i++)
    {
        Private_Key[i] = rand() % (y - x + 1) + x; // rand = 150 %10 -- > 0+1
        increasing_sum += Private_Key[i];
        x = increasing_sum + 1;
        y = x + 10; // incrementing upper limit by 10//y =12
    }
    //
    // FOR M
    int m = rand() % (y - x + 1) + x;

    for (int i = 0; i < 6; i++)
        cout << Private_Key[i] << " ";
    // FOR N
    int n, i = m / 2;
    while (1)
    {
        if (isPrime(i))
        {
            if (m % i != 0)
                break;
        }
        else
            i++;
    }
    n = i;
    // m=62 , n = 37
    // PUBLIC KEY
    int Public_key[6];
    cout << "\n\t\t******************************************************************" << endl;
    cout << "\t\tPUBLIC KEY :\t\t\t\t";
    for (int i = 0; i < 6; i++)
    {
        Public_key[i] = (Private_Key[i] * n) % m;
        cout << Public_key[i] << " ";
    }

    i = 0;
    int Cipher_Text[(s.size() / 6)];
    int j = 0, c = 1, k = 0;
    int sum = 0;

    while (i < s.size())
    {

        if (c <= 6)
        {
            sum += (s[i] - '0') * Public_key[j]; // 31, 62, 14, 90, 70, 30
            i++;
            j++;
            c++;
        }
        else
        {
            j = 0;
            c = 1;
            Cipher_Text[k] = sum;
            sum = 0;
            k++;
        }
        if (i == s.size())
        {
            Cipher_Text[k] = sum;
        }
    }

    // CIPHER TEXT
    cout << "\n\t\t******************************************************************" << endl;
    cout << "\t\tCIPHER TEXT :\t\t\t\t";
    for (int i = 0; i < (s.size() / 6); i++)
        cout << Cipher_Text[i] << " ";

    // DECRYPTION
    // m,n
    int inv_n = modInverse(n, m); // Inverse of n
    int Psuedo_Decipher[(s.size() / 6)];

    for (int i = 0; i < (s.size() / 6); i++)
    {
        Psuedo_Decipher[i] = (Cipher_Text[i] * inv_n) % m;
    }
    cout << "\n\t\t******************************************************************" << endl;
    cout << "\t\tPSEUDO DECIPHERED TEXT :\t\t";
    for (int i = 0; i < (s.size() / 6); i++)
    {
        cout << Psuedo_Decipher[i] << " ";
    }
    // 1 2 4 10 20 40
    string plain_text;
    j = 0, i = 0;
    while (1)
    {
        if (j == (s.size() / 6))
            break;
        string s1 = "000000";
        Backtracking(Private_Key, 6, Psuedo_Decipher[i], s1);
        j++;
        i++;
        plain_text += s1;
    }

    cout << "\n\t\t******************************************************************" << endl;
    cout << "\t\tDECRYPTED TEXT or PLAIN TEXT :\t\t";
    if (incrementing_zeroes_2 > 0 && incrementing_zeroes_2 < 6)
    {
        for (int i = incrementing_zeroes_2; i < plain_text.size(); i++)
        {
            cout << plain_text[i];
        }
    }
    else
        cout << plain_text;
    cout << "\n\t\t******************************************************************\n"
         << endl;
}
