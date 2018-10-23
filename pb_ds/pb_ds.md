#pb_ds的用法详讲
###1.hash（可取代map）

cc_hash_table 是拉链法
gp_hash_table 是查探法 
除了当数组用外，还支持find和operator[], 与map用法基本上一致，但是无法使用pair，struct
```C++
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
__gnu_pbds::cc_hash_table<int,bool> h1;
__gnu_pbds::gp_hash_table<int,bool> h2; // 比CC稍快
```

###2.priority——queue优先队列
1. push()  //会返回一个迭代器
2. top()  //同 stl 
3. size()  //同 stl 
4. empty() //同 stl 
5. clear()  //同 stl 
6. pop()  //同 stl 
7. join(priority_queue &other)  //合并两个堆,other会被清空
8. modify(point_iterator it,const key)  //修改一个节点的值

```C++
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds::priority_queue<int>q;//因为放置和std重复，故需要带上命名空间
__gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;//最快
__gnu_pbds::priority_queue<int,greater<int>,binary_heap_tag> pq;
__gnu_pbds::priority_queue<int,greater<int>,binomial_heap_tag> pq;
__gnu_pbds::priority_queue<int,greater<int>,rc_binomial_heap_tag> pq;
__gnu_pbds::priority_queue<int,greater<int>,thin_heap_tag> pq;//快
__gnu_pbds::priority_queue<int,greater<int> > pq;//快
```

###3.rb_tree_tag红黑树
1. 插入 ：insert(); 
2. 删除 ：erase();
3. 大小 ：size();
3. 查找k的排名 ：order_of_key(k); // 从0开始数
4. 查找排名为k的元素 ：t.find_by_order()；//实际是查询k+1大 返回的是迭代器 需要 *t.find_by_order();
5. lower_bound(x) // >= x 返回迭代器
6. upper_bound(x) // > x  返回迭代器
7. 合并 ： join(b) // b加入a，前提a，b的key不想交
8. 分类 ： split(v,b) // >v 的元素扔到b
9. 注意他没有multiset一样的功能，如果要存重复元素可以建结构体，添加一个无关变量用于区别
```C++
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t, p;

```

###4.rope平衡树

1. 运算符：rope支持operator += -= + - < ==
2. 输入输出：可以用<<运算符由输入输出流读入或输出。
3. 长度/大小：调用length()，size()都可以哦
4. 插入/添加等：
push_back(x); //在末尾添加x
insert(pos,x); //在pos插入x，自然支持整个char数组的一次插入
erase(pos,x); //从pos开始删除x个
copy(pos,len,x); //从pos开始到pos+len为止用x代替
replace(pos,x); //从pos开始换成x[pos,pos+x)
substr(pos,x); //提取pos开始x个
at(x)/[x]; //访问第x个元素 t[i], t.at(i)
        
```C++
#include <ext/rope>
using namespace __gnu_cxx;//第一条下划线其实是两条
rope<int> r;
```
