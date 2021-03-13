#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<time.h>
#include<algorithm>
using namespace std;
ifstream fin("sorts.in");
ofstream fout("sorts.out");
long long x, i, n, maxi, v[1000000], nrteste;
void random_numbers()
{
    for (long long i=0; i<n; i++)
        v[i]=rand()%(maxi+1);
}

void bubblesort()
{
    long long i, j, aux;

    for(i = 0; i <= n-2; i++)
        for(j = i+1; j < n; j++)
            if (v[i] > v[j])
            {
                aux = v[j];
                v[j] = v[i];
                v[i] = aux;
            }
}

void merge(long long a[], long long left, long long m, long long right)
{
    long long n1 = m - left + 1; // lungimea primului sub-array
    long long n2 = right - m; // lungimea celui de-al doilea sub array

    //sub-array-urile L si R pentru partitionarea vectorului
    long long L[n1], R[n2], i, j, k;

    //copiaza in array-urile L[] si R[] datele corespunzatoare

    for (i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    //in continuare, vom reconstrui array-ul

    //index-ul initial al primului sub-array
    i = 0;

    // index-ul initial al celui de-al doilea sub-array
    j = 0;

    // index-ul initial al imbinarii celor doua sub-array-uri
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    //Copiem inapoi in vector elementele ramase in sub-array-ul L
    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    //Copiem elementele inapoi in vector elementele ramase in sub-array-ul R
    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(long long a[],long long left, long long right)
{

    if(left>=right)
    {
        return;
        //return recursiv => am ajuns la finalul sortarii
    }
    long long m = left+ (right-left)/2; // calculam mijlocul array-ului
    mergeSort(a,left,m);
    mergeSort(a,m+1,right);
    merge(a,left,m,right);
}

long long partition(long long Array[], long long left, long long right)
{
    long long i, pivot, aux;
    i = left; // i este index-ul initial
    pivot = Array[right]; // alegem ca pivot ultimul element din array

    //intr-o lista avem elem mai mici decat pivotul, iar in cealalta pe cele mai mari decat pivotul
    for(long long j = left; j <=right; j++)
    {
        if(Array[j] < pivot)
        {
            aux = Array[i];
            Array[i] = Array[j];
            Array[j] = aux;
            i++;
        }
    }
    aux = Array[right];
    Array[right] = Array[i];
    Array[i] = aux;
    return i;
}



void quicksort(long long Array[], long long left, long long right)
{
    if (left < right)
    {
        long long pivot;
        pivot = partition(Array, left, right);
        quicksort(Array, left, pivot-1);
        quicksort(Array, pivot+1, right);
    }
}

void countSort(long long Array[], long long n)
{
    long long max = 0;

    // identificam cel mai mare element din array
    for (long long i=0; i<n; i++)
    {
        if(max < Array[i])
        {
            max = Array[i];
        }
    }

    // cream un array de frecventa de dimensiunea maximului+1
    // il populam inilial cu zero, apoi incrementam casutele cu indexii corespunzatori numerelor din array-ul initial
    long long freq[max+1];
    for (long long i=0; i<max+1; i++)
    {
        freq[i] = 0;
    }
    for (long long i=0; i<n; i++)
    {
        freq[Array[i]]++;
    }

    // sortam array-ul initial folosindu-ne de tabloul de frecventa creat
    for (long long i=0, j=0; i<=max; i++)
    {
        while(freq[i]>0)
        {
            Array[j] = i;
            j++;
            freq[i]--;
        }
    }
}

void countingsort(long long vector[], long long n, long long current)
{
    long long output[n], i, frecv[10] = {0}; // array-ul frecv stocheaza frecventa cifrelor de la 0 la 9

    //incrementam array-ul frecv de fiecare data cand identificam un (nr din array)/current care se termina cu una din cifrele 0-9
    for(i = 0; i < n; i++)
        frecv[(vector[i]/current)%10]++;

    // adunam casuta precedenta la casuta actuala
    for (i = 1; i < 10; i++)
        frecv[i] += frecv[i - 1];

    //construim array-ul pentru output
    for (i = n - 1; i >= 0; i--)
    {
        output[frecv[(vector[i]/current)%10] - 1] = vector[i];
        frecv[(vector[i]/current)%10]--;
    }

    //copiem array-ul output peste array-ul ce trebuia sortat initial
    for (i = 0; i < n; i++)
        vector[i] = output[i];
}

void radixsort(long long vector[], long long n)
{
    long long maximm = vector[0], i, current;

    //identificam maximul din array
    for (i=1; i<n; i++)
    {
        if(maximm < vector[i])
            maximm = vector[i];
    }

    //aplicam counting sort pe fiecare locatie, numarul fiind verficicat de la unitati catre sute, mii, etc;
    //cat timp maximm/current este mai mare decat 0
    for (current = 1; maximm/current > 0; current *= 10)
        countingsort(vector, n, current);
}


void sortcode(long long array[], long long n)
{
    sort(array, array+n);
}
int main ()
{
    srand(time(NULL));
    fin>>nrteste;
    while(nrteste)

    {
        clock_t start, stop;
        start = clock();
        double executionTime;
        fin>>n>>maxi;
        nrteste--;
        random_numbers();
        //alegeti cate una din sortarile de mai jos, iar pe restul comentati-le, pentru a observa timpii de rulare in fisierul sorts.out
        bubblesort();
        mergeSort(v, 0, n - 1);
        quicksort(v, 0, n - 1);
        countSort(v, n);
        radixsort(v, n);
        sortcode(v, n);

        stop = clock();
        executionTime = ((double)(stop) - (double)(start)) / CLOCKS_PER_SEC;

        fout << executionTime << " s" << endl;
        for (int i=0; i<n; i++)
            fout<<v[i]<<" ";
        fout<<endl;
    }
    return 0;
}
