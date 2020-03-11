//数字的正－倒序输出
#include<stdio.h>
int main(void) {
	/* 这里先定义几个后面都用的上的变量，大家后面再细看
	   为了保证用户输入一个很大的数值也能计算，使用长整型变量 */
	long long temp, t1, t2, t3;
	
	long long a, i = 0, s = 1;
	printf("请输入一个数值：");
	scanf("%lld", &a);
	t1 = t2 = t3 = a;	/*这几个变量都是后面用的上
				  因为下面的操作需要对变量进行修改
				  所以需要把用户的输入同时赋给几个变量
				  才能正常进行下面的多个循环操作  */
	printf("\n\n");
	
	//第一阶段--计算位数
	while (a != 0) {		//当a的余数不为0时执行这个循环
	a /= 10;			//对输入的数（十进制）整除!0
	i++;				//计算位数--每循环一次就加1
	s *= 10;			//这个s是最后面循环那用的，先不用理它
	}
	
	printf("输入的位数有%lld位 \n", i);	//输出循环的次数，也就是位数

	printf("\n");
	
	//第二阶段--在文本输出上下点功夫输出倒序 	
	/*
	   我们先直接求倒序输出吧，下面的代码循环一次就打印一个余数
	   这样可以直接在文本形式上输出倒序了
	   怎么输出正序？ ...直接printf()啊，用户自己输入的数不就是正序吗 （滑稽
	*/	
	printf("正序的数值：%lld \n", t1);
	printf("倒序的数值："); 		//注意一下这里的输出格式，其实安排的很有技巧
	while (t1 != 0) {
	temp = t1 % 10;
	printf("%lld", temp);
	t1 = t1 / 10;
	}
			
	//第三阶段--真正的数值排序
	/* 
	   刚刚的利用数字文本的输出方式来排序比较简单
	   但是我们想把排好的数值存进变量使用，要怎么办呢？
	   所以下面的方法与上面的完全不同，我们可以用这个方法
	   完全重组用户输入的十进制数值
	   我们先排正序试试？想想如何利用十进制数的特性 
	   假设有一个数字15243，我们按进制数位来拆开它，是不是可以拆成（从个位开始）：
	   15243 = 3*1 + 4*10 + 2*100 + 5*1000 + 1*10000
	   没错！利用上面的特性，结合第一个循环
	   我们可以试着对数字先求余，保存它的余数之后
	   再让数字整除10，让它减少一位，这样就可以做成一个循环了
	   由于第一个余数乘的进制位数是1，而每次循环进制位数都会累乘一次10
	   所以3是最低位的数值（个位），1就是最高位（万位）的数值了，正序输出完成！
	   还要注意一下，我们利用的是同一个求余算法求出的余数，所以第一个余数总会是3
	   如果我们要求倒序，不如直接让3乘以最高位进制数好了，就像这样：
	   34251 = 3*10000 + 4*1000 + 2*100 + 5*10 + 1*1 
	   同上所述，这里数值按进制位排列的方式也是一样的
	   只是这次让正序中最高位的数换了位置
	   这样我们就可以重复利用一个循环中的余数来计算了
	*/

	printf("\n\n");
	
	//我们把排好的数存进p1,p2两个变量中吧	
	long long p1 = 0, p2 = 0;
	long long k1, k2;
	
	//第一个版本的输出排序 
	for (temp = 0, k1 = 1, k2 = 10000; t2 != 0; k1 *= 10, k2 /= 10) {
	temp = t2 % 10;
	p1 = p1 + (temp * k1);
	p2 = p2 + (temp * k2);
	t2 = t2 / 10;
	}
	printf("现在的数值存到了变量中 \n"
	       "正序输出：%lld\n"
	       "倒序输出：%lld \n\n", p1, p2);
	
	/* 
	看起来好像不错！但是由于在for循环中k2的值是10000
	这是一个数值常量，所以这个循环最大的位数排序范围就只能是万位以内的数了
	我们不如从开头计算位数的循环中借点道
	在循环中插入一个s来计算最高进制位的数作为乘数
	每循环一次,s就会乘10，这样就可以按用户输入的数值得到一个可以变化的最高进制位了
	*/
	
	//我们先检查一下s的值是多少吧
	printf("s = %lld \n", s);
	/* 
	注意了，s的输出值似乎比用户输入的数值多了一位！
	跟我们想的不大一样，开头的循环好像执行了6次！
	不过不要紧，我们只要除个10，消去一位，下面的循环结果就对了
	*/
	s = s /10;
	printf("处理后，最高进制位为%lld \n", s);
	p1 = p2 = 0;
	//第二个版本的循环
	for (temp = 0,k1 = 1, k2 = s; t3 != 0; k1 *= 10, k2 /= 10) {
	temp = t3 % 10;
	p1 = p1 + (temp * k1);
	p2 = p2 + (temp * k2);
	t3 = t3 / 10;
	}
	
	printf("现在的数值重新存到了变量中 \n"
	       "正序输出：%lld\n"
	       "倒序输出：%lld\n", p1, p2);
	
	return 0;
}
