#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
void Create(int *array);
void Output(int *array);
void InsertSort(int *array);  //ֱ�Ӳ�������
void BInsertSort(int *array);   //�۰��������
void ShellInsert(int *array,int increment);   //ϣ������
void ShellSort(int *array);
void BubbleSort(int *array);  //ð������
int Partition(int *array,int low,int high);  //��������
void QSort(int *array,int low,int high);
void QuickSort(int *array);
void SelectSort(int *array);  //��ѡ������
void Merge(int *TempMem,int *SrcMem,int left,int mid,int right);  //�鲢����
void MSort(int *TempMem,int *SrcMem,int left,int right);  //��·�����ڹ鲢
void MergeSort(int *array);
void MaxHeapify(int *array, int start, int end);   //�Ѵ󶥻�����
void HeapSort(int *array);  //������
void order(void);
void Sort(int *array,int num);
void MergeSortURec(int *array);
void MergeOnce(int *array,int *temp,int step);
int count=1;    //ÿ�δ����������Ԫ�ظ���,�±�0�������ø����򷽷��е��ڱ�
/*
4 7 1 0 2 18 24 15 q  8����
*/
int main(void)
{
    int array[100]={0},num;
    Create(array);
    
    order();
    scanf("%d",&num);
    Sort(array,num);
    Output(array);
    return 0;
}
void order(void)
{
    printf(
           "1. ֱ�Ӳ�������\n"
           "2. �۰��������\n"
           "3. ϣ������\n"
           "4. ð������\n"
           "5. ��������\n"
           "6. ��ѡ������\n"
           "7. �鲢����\n"
           "8. ������\n");
    printf("������������ţ�");
}
void Sort(int *array,int num)
{
    switch(num)
    {
        case 1: InsertSort(array);break;
        case 2: BInsertSort(array);break;
        case 3: ShellSort(array);break;
        case 4: BubbleSort(array);break;
        case 5: QuickSort(array);break;
        case 6: SelectSort(array);break;
        case 7: MergeSort(array);break;
        case 8: HeapSort(array);break;
    }
}
void MaxHeapify(int *array, int start, int end)
{
    int dad=start,temp,son=dad*2;;  //���׽ڵ�ͺ��ӽڵ��±�
    while (son<=end)
    {
        if(son+1<=end&&array[son]<array[son+1]) //�ȱȽ������ӽڵ��С��ѡ������
            son++;
        if(array[dad]>array[son]) //���ڵ���ں��ӽڵ���������ϣ�ֱ����������
            return;
        else  //���򽻻�˫�׺ͺ��ӵ������ټ����ӽڵ����ڵ�Ƚ�
        {
            temp=array[dad];
            array[dad]=array[son];
            array[son]=temp;
            dad=son;
            son=dad*2;
        }
    }
}
void HeapSort(int *array)
{
    int i,temp;
    for (i=count/2;i>0;i--)  //�����һ�����ڵ㿪ʼ����
        MaxHeapify(array,i,count);
    //�Ƚ���һ��Ԫ�غ����ź�Ԫ��ǰһλ�������������µ�����ֱ���������
    for (i=count;i>1;i--)
    {
        temp=array[1];
        array[1]=array[i];
        array[i]=temp;
        MaxHeapify(array,1,i-1);   //��array[1..i-1]���µ���Ϊ�󶥶�
    }
}
void Merge(int *TempMem,int *SrcMem,int left,int mid,int right)//��TempMem�����е�������left-mid��mid+1-right�ϲ�
{
    int i,j,k;   //�������������С�α�ʹ�ŵ���ԭ�洢���α�
    for(i=left,j=mid+1,k=i;i<=mid&&j<=right;k++)
    {
        if(TempMem[i]<TempMem[j])
            SrcMem[k]=TempMem[i++];
        else
            SrcMem[k]=TempMem[j++];
    }
    if(i<=mid)
    {
        for(;i<=mid;i++)
            SrcMem[k++]=TempMem[i];
    }
    if(j<=right)
    {
        for(;j<=right;j++)
            SrcMem[k++]=TempMem[j];
    }
}
void MergeOnce(int *array,int *temp,int step)
{
	int i,j;
	for(i=1;i<=count-2*step+1;i+=2*step)
	{
		Merge(array,temp,i,i+step,i+2*step);
	}
	if(i+step<count+2)
		Merge(array,temp,i,i+step,count);
	else
		for(j=i;j<=count;j++)  temp[j]=array[j];
	for(i=1;i<=count;i++)
		array[i]=temp[i];
 } 
void MergeSortURec(int *array)
{
	int *temp,step=1;
	temp=(int *)malloc(sizeof(int)*count);
	while(step<=count)
	{
		MergeOnce(array,temp,step);
		step*=2;
	}
}
void MSort(int *TempMem,int *SrcMem,int left,int right)  //��·�����ٹ鲢�ݹ� 
{
    int mid=(left+right)/2;
    int TempMem0[100];
    if(left==right)  SrcMem[left]=TempMem[left];
    else
    {
        MSort(TempMem,TempMem0,left,mid);
        MSort(TempMem,TempMem0,mid+1,right);
        Merge(TempMem0,SrcMem,left,mid,right);
    }
}
void MergeSort(int *array)
{
    MSort(array,array,1,count);
}
void SelectSort(int *array)
{
    int i,j,min,temp;
    for(i=1;i<=count-1;i++)
    {
        min=i;   //����i����Ϊ��С�ģ������Ƚ�ʱmin�ĳ�ֵΪi
        for(j=i+1;j<=count;j++)
        {
            if(array[j]<array[min])
            {
                min=j;
            }
        }
        temp=array[min];
        array[min]=array[i];
        array[i]=temp;
    }
}
int Partition(int *array,int low,int high)
{
    int pivotKey=array[low];
    array[0]=array[low];
    while(low<high)
    {
        while(low<high&&array[high]>=pivotKey) high--;
        array[low]=array[high];
        while(low<high&&array[low]<=pivotKey)  low++;
        array[high]=array[low];
    }
    array[low]=array[0];
    return low;
}
void QSort(int *array,int low,int high)
{
    int pivot;
    if(low<high)
    {
        pivot=Partition(array,low,high);
        QSort(array,low,pivot-1);
        QSort(array,pivot+1,high);
    }
}
void QuickSort(int *array)
{
    QSort(array,1,count);
}
void BubbleSort(int *array)
{
    int i,j,temp;
    for(i=count;i>=2;i--)  //�ܹ���Ҫ��n-1������������
    {
        for(j=1;j<=i-1;j++)
        {
            if(array[j]>array[j+1])
            {
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
}
void ShellInsert(int *array,int increment)
{
    int i,j;
    for(i=1+increment;i<=count;i++)
    {
        if(array[i]<array[i-increment])
        {
            array[0]=array[i];
            for(j=i-increment;j>0&&array[0]<array[j];j-=increment)
                array[j+increment]=array[j];
            array[j+increment]=array[0];  //���뵽��ȷ��λ��
        }
    }
}
void ShellSort(int *array)
{  //�ڲ�������������
    int delta[10]={0},num=0,i=0,j;
    num=count/2;
    while(num>=1)
    {
        delta[i]=num;
        num-=2;
        i++;
        if(num==2)
        {
            delta[i]=num;
            delta[i+1]=num-1;
            i+=2;
            break;
        }
    }
    for(j=0;j<i;j++)
        ShellInsert(array,delta[j]);
}
void BInsertSort(int *array)
{
    int i,j;
    int high,low,mid;
    for(i=2;i<=count;i++)
    {
        if(array[i]<array[i-1])
        {
            low=1;
            high=i-1;  //�������еĸ�λ�͵�λ�α�
            array[0]=array[i];
            while(low<=high)  //���ֲ���ȷ������λ��
            {
                mid=(low+high)/2;
                if(array[mid]>array[0])
                    high=mid-1;
                else
                    low=mid+1;
            }
            for(j=i-1;j>=high+1;j--)  //ע���ʱ�ض����Ҳ��ɹ������ÿ�β��Һ����λ�þ�Ϊhigh+1;
                    array[j+1]=array[j];
            array[j+1]=array[0];  //���뵽��ȷ��λ��
        }
    }
}
void InsertSort(int *array)
{
    int i,j;
    for(i=2;i<=count;i++)
    {
        if(array[i]<array[i-1])
        {
            array[0]=array[i];
            for(j=i-1;array[j]>array[0];j--)
                array[j+1]=array[j];
            array[j+1]=array[0];  //���뵽��ȷ��λ��
        }
    }
}
void Output(int *array)
{
    int i;
    printf("���������Ϊ��\n");
    for(i=1;i<=count;i++)
        printf("%d\t",array[i]);
}
void Create(int *array)
{
    count=1;
    printf("������Ҫ�����������Ԫ��ֵ,q���������룺");
    while(scanf("%d",array+count))
        count++;
    count--;
    getchar();
}
