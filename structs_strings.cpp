#include<stdio.h>
#include<algorithm>
using namespace std;
const int maxn=100+10;
int cs=0,n,m;
int inter_width[maxn],inter_height[maxn];
int up[maxn],down[maxn],left[maxn],right[maxn];
int ind[maxn],outer[maxn];
double width[maxn],height[maxn],x[maxn],y[maxn];	//原来的窗口
double nx[maxn],ny[maxn],nwidth[maxn],nheight[maxn];	//调整过后的窗口
/**
调整前第i个窗口左上方角落相对于其外层窗口左上方角落的位移为x[i]和y[i]、初始的宽度和高度为width[i]和height[i],调整后的坐标为nx[i], ny[i]， 宽度为nwidth[i]，高度为nheight[i]
**/
bool cmp_is_child(const int &a,const int &b)
{
	/**
	function:判断a是否是b的子窗口
	**/
	double A = x[a]+y[a];
	double B = x[b]+y[b];
	return A<B;
}
 
int main()
{
	
	while(1)
	{	

		// 第一阶段： 输入
		scanf("%d%d%lf%lf",&n,&m,&width[0],&height[0]);
		/**
		当n为0的时候表示输入结束
		**/
		if(!n)
			break;//退出循环，否则一直检测输入，直到输入0 0 0 0
		cs++;
		//反复输入窗口数，外层窗口被调整大小的次数和最外层窗口的宽和高的初始值
		x[0]=y[0]=nx[0]=ny[0]=ind[0]=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%lf%lf%lf%lf",&x[i],&y[i],&width[i],&height[i]);
				//输入第i个窗口左上方角落相对于其外层窗口左上方角落的位移、初始的宽度和高度
			scanf("%d%d%d%d%d%d",&inter_width[i],&inter_height[i],&up[i],&down[i],&left[i],&right[i]);
				//输入连接第i个窗口垂直边的弹簧撑杆标志ho[i]和水平边的弹簧撑杆标志hove[i],
				//上下左右四条边和外层窗口对应边的弹簧撑杆标志up[i]、down[i]、left{i]和right[i]
				//1表示弹簧,0表示支撑杆
			ind[i]=i;
			if(inter_width[i]+left[i]+right[i]==0)
				right[i]=1;//若第i个窗口的垂直边、左右两边与外层窗口对应边间用撑杆连接，则右边与外层窗口对应边间改用弹簧
			if(inter_height[i]+up[i]+down[i]==0)
				up[i]=1;//若第i个窗口的水平边、上下两边与外层窗口对应边间用撑杆连接，则上边与外层窗口对应边间改用弹簧
		}
		/**
		n个窗口按照由外向内(位移和递增)的顺序排列成ind序列
		**/
		sort(ind+1,ind+n+1,cmp_is_child);
		
		
		// 第二阶段： 寻找外嵌窗口
		for(int i=1;i<=n;++i)
			for(int j=i-1;j>=0;--j)
				if(x[ind[j]]<x[ind[i]]&&y[ind[j]]<y[ind[i]]&&x[ind[j]]+width[ind[j]]>x[ind[i]]+width[ind[i]]
				&&y[ind[j]]+height[ind[j]]>y[ind[i]]+height[ind[i]])
				{	//ind序列中第j个窗口是第i个窗口的外嵌窗口
					outer[ind[i]]=ind[j];
					break;
				}
				
				
				
		// 第三阶段：调整
		for(int i=n;i>0;--i){	//计算每个窗口与外嵌窗口间x坐标和y坐标的调整空间
			x[ind[i]]-=x[outer[ind[i]]];
			y[ind[i]]-=y[outer[ind[i]]];
		}
		for(int q=1;q<=m;++q)	//输入每次调整外层窗口新的宽和高
		{	
			scanf("%lf%lf",&nwidth[0],&nheight[0]);
				//从外到内更新每个窗
			for(int i=1,cur;i<=n;++i)
			{
				/**
				进行调整量的计算
				**/
				cur=ind[i];	//取出从外到内的第i个窗口
				double w0=0,h0=0;	//w0是当前窗口宽度的调整量，h0是当前窗口高度的调整量
				w0 = ((!inter_width[cur])?width[cur]:0) + ((!left[cur])?x[cur]:0) + ((!right[cur])?(width[outer[cur]]-width[cur]-x[cur]):0);
				h0 = ((!inter_height[cur])?height[cur]:0) + ((!up[cur])?y[cur]:0) + ((!down[cur])?(height[outer[cur]]-height[cur]-y[cur]):0);
				nwidth[cur]=inter_width[cur]?width[cur]*(nwidth[outer[cur]]-w0)/(width[outer[cur]]-w0):nwidth[cur]=width[cur];//若该窗口水平连接是弹簧，则计算调整后的宽度
				nheight[cur]=inter_height[cur]?height[cur]*(nheight[outer[cur]]-h0)/(height[outer[cur]]-h0):nheight[cur]=height[cur];//若该窗口垂直连接是弹簧，则计算调整后的高度
				ny[cur]=up[cur]?y[cur]*(nheight[outer[cur]]-h0)/(height[outer[cur]]-h0):ny[cur]=y[cur];//若该窗口上方连接是弹簧，则计算调整后的y坐标的增量
				nx[cur]=left[cur]?x[cur]*(nwidth[outer[cur]]-w0)/(width[outer[cur]]-w0):nx[cur]=x[cur];//若该窗口左方连接是弹簧，则计算调整后的y坐标的增量
			}
			/**
			进行打印输出，格式参见pdf文件的output
			**/
			for(int i=1;i<=n;++i)	//计算调整后的x左边和y坐标
				nx[ind[i]]+=nx[outer[ind[i]]],ny[ind[i]]+=ny[outer[ind[i]]];
			printf("Case %d, resize operation %d:\n",cs,q);	//输出测试用例编号和调整操作编号
			for(int i=1;i<=n;++i)	//输出每个窗口的编号、坐标、宽度和高度
				printf("    Window %d, x = %.0lf, y = %.0lf, width = %.0lf, height = %.0lf\n",i,nx[i],ny[i],nwidth[i],nheight[i]);
		}
	}
	return 0;
}