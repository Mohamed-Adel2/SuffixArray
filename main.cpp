#include <iostream>

using namespace std;

class Node{
public:
    int indx,r1,r2;
};

void SortbyRank(Node* nums,int start,int mid,int end)
{
    int leftLength=mid-start+1;
    int rightLength=end-mid;

    Node* left=new Node[leftLength];
    Node* right=new Node[rightLength];

    for(int i=0;i<leftLength;i++)
    {
        left[i]=nums[start+i];
    }

    for(int j=0;j<rightLength;j++)
    {
        right[j]=nums[mid+1+j];
    }

    int i = 0, j = 0, k = start;

    while(i<leftLength && j<rightLength)
    {
        if(left[i].r1<right[j].r1 || (left[i].r1==right[j].r1 && left[i].r2<right[j].r2))
        {
            nums[k]=left[i];
            i++;
        }
        else
        {
            nums[k]=right[j];
            j++;
        }
        k++;
    }
    while(i<leftLength)
    {
        nums[k]=left[i];
        i++;
        k++;
    }

    while(j<rightLength)
    {
        nums[k]=right[j];
        j++;
        k++;
    }
}
void SortbyRank(Node* nums,int start,int end)
{
    if(start<end)
    {
        int mid = (start + end) / 2;
        SortbyRank(nums, start, mid);
        SortbyRank(nums, mid + 1, end);
        SortbyRank(nums, start, mid, end);
    }
}
void SortbyIndx(Node* nums, int start, int mid, int end)
{
    int leftLength=mid-start+1;
    int rightLength=end-mid;

    Node* left=new Node[leftLength];
    Node* right=new Node[rightLength];

    for(int i=0;i<leftLength;i++)
    {
        left[i]=nums[start+i];
    }

    for(int j=0;j<rightLength;j++)
    {
        right[j]=nums[mid+1+j];
    }

    int i=0,j=0,k=start;

    while(i<leftLength && j<rightLength)
    {
        if(left[i].indx<right[j].indx)
        {
            nums[k]=left[i];
            i++;
        }
        else
        {
            nums[k]=right[j];
            j++;
        }
        k++;
    }

    while(i<leftLength)
    {
        nums[k]=left[i];
        i++;
        k++;
    }

    while(j<rightLength)
    {
        nums[k]=right[j];
        j++;
        k++;
    }
}
void SortbyIndx(Node* nums, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        SortbyIndx(nums, start, mid);
        SortbyIndx(nums, mid + 1, end);
        SortbyIndx(nums, start, mid, end);
    }
}

int Power(int number,int pow)
{
    if(pow==0)return 1;
    if(pow==1)return number;
    int tmp;
    if(pow%2==0)
    {
        tmp=Power(number,pow/2);
        return tmp*tmp;
    }
    else
    {
        tmp=Power(number,(pow+1)/2);
        return tmp*tmp/number;
    }
}

int Logbase2(int number)
{
    int count=0;
    double n=number;
    while(n/2>0 && n>=2)
    {
        n/=2;
        count++;
    }
    if(n==1)return count;
    return count+1;
}


class SuffixArray{
public:
    Node* arr;
    int len;
    void getLength(char s[])
    {
        int len=0;
        while(s[len]!='\0') len++;
        this->len=len;
    }

    void updater1()
    {
        int tmp=arr[0].r1;
        arr[0].r1=0;
        for(int i=1;i<len;i++)
        {
            if(arr[i].r1==tmp && arr[i].r2==arr[i-1].r2)arr[i].r1=arr[i-1].r1;
            else
            {
                tmp=arr[i].r1;
                arr[i].r1=arr[i-1].r1+1;
            }
        }
    }

    void updater2(int num)
    {
        for(int i=0;i<len;i++)
        {
            if(i<=len-1-num) arr[i].r2=arr[i+num].r1;
            else arr[i].r2=-100;
        }
    }

    SuffixArray(char s[])
    {
        getLength(s);
        arr=new Node[len];
        for(int i=0;i<len;i++)
        {
            arr[i].indx=i;
            arr[i].r1=s[i]-'A';
            arr[i].r2=-1;
        }
    }

    void ConstructUsingPrefixDoubling()
    {
        for(int i=0;i<Logbase2(len);i++)
        {
            SortbyRank(arr,0,len-1);
            updater1();
            SortbyIndx(arr,0,len-1);
            updater2(Power(2,i));
        }
        SortbyRank(arr,0,len-1);
    }

    void Print()
    {
        for(int i = 0; i < len; i++)
        {
            cout << arr[i].indx << " ";
        }
        cout<<endl;
    }

};
