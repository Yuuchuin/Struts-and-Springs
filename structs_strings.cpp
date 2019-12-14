#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn=100+10;
int cs=0,n,m;
int inter_width[maxn],inter_height[maxn];
int up[maxn],down[maxn],left[maxn],right[maxn];
int ind[maxn],outer[maxn];
double width[maxn],height[maxn],x[maxn],y[maxn];	//ԭ���Ĵ���
double nx[maxn],ny[maxn],nwidth[maxn],nheight[maxn];	//��������Ĵ���
/**
����ǰ��i���������Ϸ��������������㴰�����Ϸ������λ��Ϊx[i]��y[i]����ʼ�Ŀ�Ⱥ͸߶�Ϊwidth[i]��height[i],�����������Ϊnx[i], ny[i]�� ���Ϊnwidth[i]���߶�Ϊnheight[i]
**/
bool cmp_is_child(const int &a,const int &b)
{
	/**
	function:�ж�a�Ƿ���b���Ӵ���
	**/
	double A = x[a]+y[a];
	double B = x[b]+y[b];
	return A<B;
}
 
int main()
{
	
	while(1)
	{	

		// ��һ�׶Σ� ����
		scanf("%d%d%lf%lf",&n,&m,&width[0],&height[0]);
		/**
		��nΪ0��ʱ���ʾ�������
		**/
		if(!n)
			break;//�˳�ѭ��������һֱ������룬ֱ������0 0 0 0
		cs++;
		//�������봰��������㴰�ڱ�������С�Ĵ���������㴰�ڵĿ�͸ߵĳ�ʼֵ
		x[0]=y[0]=nx[0]=ny[0]=ind[0]=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%lf%lf%lf%lf",&x[i],&y[i],&width[i],&height[i]);
				//�����i���������Ϸ��������������㴰�����Ϸ������λ�ơ���ʼ�Ŀ�Ⱥ͸߶�
			scanf("%d%d%d%d%d%d",&inter_width[i],&inter_height[i],&up[i],&down[i],&left[i],&right[i]);
				//�������ӵ�i�����ڴ�ֱ�ߵĵ��ɳŸ˱�־ho[i]��ˮƽ�ߵĵ��ɳŸ˱�־hove[i],
				//�������������ߺ���㴰�ڶ�Ӧ�ߵĵ��ɳŸ˱�־up[i]��down[i]��left{i]��right[i]
				//1��ʾ����,0��ʾ֧�Ÿ�
			ind[i]=i;
			if(inter_width[i]+left[i]+right[i]==0)
				right[i]=1;//����i�����ڵĴ�ֱ�ߡ�������������㴰�ڶ�Ӧ�߼��óŸ����ӣ����ұ�����㴰�ڶ�Ӧ�߼���õ���
			if(inter_height[i]+up[i]+down[i]==0)
				up[i]=1;//����i�����ڵ�ˮƽ�ߡ�������������㴰�ڶ�Ӧ�߼��óŸ����ӣ����ϱ�����㴰�ڶ�Ӧ�߼���õ���
		}
		/**
		n�����ڰ�����������(λ�ƺ͵���)��˳�����г�ind����
		**/
		sort(ind+1,ind+n+1,cmp_is_child);
		
		
		// �ڶ��׶Σ� Ѱ����Ƕ����
		for(int i=1;i<=n;++i)
			for(int j=i-1;j>=0;--j)
				if(x[ind[j]]<x[ind[i]]&&y[ind[j]]<y[ind[i]]&&x[ind[j]]+width[ind[j]]>x[ind[i]]+width[ind[i]]
				&&y[ind[j]]+height[ind[j]]>y[ind[i]]+height[ind[i]])
				{	//ind�����е�j�������ǵ�i�����ڵ���Ƕ����
					outer[ind[i]]=ind[j];
					break;
				}
				
				
				
		// �����׶Σ�����
		for(int i=n;i>0;--i){	//����ÿ����������Ƕ���ڼ�x�����y����ĵ����ռ�
			x[ind[i]]-=x[outer[ind[i]]];
			y[ind[i]]-=y[outer[ind[i]]];
		}
		for(int q=1;q<=m;++q)	//����ÿ�ε�����㴰���µĿ�͸�
		{	
			scanf("%lf%lf",&nwidth[0],&nheight[0]);
				//���⵽�ڸ���ÿ����
			for(int i=1,cur;i<=n;++i)
			{
				/**
				���е������ļ���
				**/
				cur=ind[i];	//ȡ�����⵽�ڵĵ�i������
				double w0=0,h0=0;	//w0�ǵ�ǰ���ڿ�ȵĵ�������h0�ǵ�ǰ���ڸ߶ȵĵ�����
				w0 = ((!inter_width[cur])?width[cur]:0) + ((!left[cur])?x[cur]:0) + ((!right[cur])?(width[outer[cur]]-width[cur]-x[cur]):0);
				h0 = ((!inter_height[cur])?height[cur]:0) + ((!up[cur])?y[cur]:0) + ((!down[cur])?(height[outer[cur]]-height[cur]-y[cur]):0);
				nwidth[cur]=inter_width[cur]?width[cur]*(nwidth[outer[cur]]-w0)/(width[outer[cur]]-w0):nwidth[cur]=width[cur];//���ô���ˮƽ�����ǵ��ɣ�����������Ŀ��
				nheight[cur]=inter_height[cur]?height[cur]*(nheight[outer[cur]]-h0)/(height[outer[cur]]-h0):nheight[cur]=height[cur];//���ô��ڴ�ֱ�����ǵ��ɣ�����������ĸ߶�
				ny[cur]=up[cur]?y[cur]*(nheight[outer[cur]]-h0)/(height[outer[cur]]-h0):ny[cur]=y[cur];//���ô����Ϸ������ǵ��ɣ������������y���������
				nx[cur]=left[cur]?x[cur]*(nwidth[outer[cur]]-w0)/(width[outer[cur]]-w0):nx[cur]=x[cur];//���ô����������ǵ��ɣ������������y���������
			}
			/**
			���д�ӡ�������ʽ�μ�pdf�ļ���output
			**/
			for(int i=1;i<=n;++i)	//����������x��ߺ�y����
				nx[ind[i]]+=nx[outer[ind[i]]],ny[ind[i]]+=ny[outer[ind[i]]];
			printf("Case %d, resize operation %d:\n",cs,q);	//�������������ź͵����������
			for(int i=1;i<=n;++i)	//���ÿ�����ڵı�š����ꡢ��Ⱥ͸߶�
				printf("    Window %d, x = %.0lf, y = %.0lf, width = %.0lf, height = %.0lf\n",i,nx[i],ny[i],nwidth[i],nheight[i]);
		}
	}
	return 0;
}