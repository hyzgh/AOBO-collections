#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;

#define ALLEDGES ((1 << 19) - 2)

typedef pair<int,int> pii;

map<pii, int> edgeID;
int triangle[9];

// 给边和三角形编码
void encode() {
	edgeID[pii(1, 2)] = 1 << 1; edgeID[pii(1, 3)] = 1 << 2; edgeID[pii(2, 3)] = 1 << 3;
	edgeID[pii(2, 4)] = 1 << 4; edgeID[pii(2, 5)] = 1 << 5; edgeID[pii(3, 5)] = 1 << 6;
	edgeID[pii(3, 6)] = 1 << 7; edgeID[pii(4, 5)] = 1 << 8; edgeID[pii(5, 6)] = 1 << 9;
	edgeID[pii(4, 7)] = 1 << 10; edgeID[pii(4, 8)] = 1 << 11; edgeID[pii(5, 8)] = 1 << 12;
	edgeID[pii(5, 9)] = 1 << 13; edgeID[pii(6, 9)] = 1 << 14; edgeID[pii(6, 10)] = 1 << 15;
	edgeID[pii(7, 8)] = 1 << 16; edgeID[pii(8, 9)] = 1 << 17; edgeID[pii(9, 10)] = 1 << 18;

	triangle[0] = (1 << 1) + (1 << 2) + (1 << 3);
	triangle[1] = (1 << 4) + (1 << 5) + (1 << 8);
	triangle[2] = (1 << 3) + (1 << 5) + (1 << 6);
	triangle[3] = (1 << 6) + (1 << 7) + (1 << 9);
	triangle[4] = (1 << 10) + (1 << 11) + (1 << 16);
	triangle[5] = (1 << 8) + (1 << 11) + (1 << 12);
	triangle[6] = (1 << 12) + (1 << 13) + (1 << 17);
	triangle[7] = (1 << 9) + (1 << 13) + (1 << 14);
	triangle[8] = (1 << 14) + (1 << 15) + (1 << 18);
}

// 计算新添加一条边可以获得的分数
int count(int status, int edgeID) {
	int ans = 0;
	for(int i = 0; i < 9; i++) {
		if((triangle[i] & edgeID) && (triangle[i] & status) == triangle[i])
			ans++;
	}
	return ans;
}

int findMax(int beta, int status, int score);

// 从当前状态status出发，搜索能取到的最低分
int findMin(int alpha, int status, int score) {
	// 所有的边都已经添加完，返回
	if(status == ALLEDGES)
		return score;
	int t = 1;
	// 枚举剩余可取的边
	int remain = ~status & ALLEDGES;
	while(remain) {
		int i = remain & -remain;
		int newStatus = status | i;
		int cnt = count(newStatus, i);
		// 假如添加一边有得分，则可以继续再走一步，否则轮到对方走
		t = cnt ? min(t, findMin(alpha, newStatus, score - cnt)) : min(t, findMax(t, newStatus, score));
		// alpha剪枝
		if(t <= alpha)
			return alpha;
		remain -= i;
	}
	return t;
}

// 从当前状态status出发，搜索能取到的最高分
int findMax(int beta, int status, int score) {
	// 所有的边都已经添加完，返回
	if(status == ALLEDGES)
		return score;
	int t = -1;
	// 枚举剩余可取的边
	int remain = ~status & ALLEDGES;
	while(remain) {
		int i = remain & -remain;
		int newStatus = status | i;
		int cnt = count(newStatus, i);
		// 假如添加一边有得分，则可以继续再走一步，否则轮到对方走
		t = cnt ? max(t, findMax(beta, newStatus, score + cnt)) : max(t, findMin(t, newStatus, score));
		// beta剪枝
		if(t >= beta)
			return beta;
		remain -= i;
	}
	return t;
}

int main(void) {
	encode();
	int allKase, edgeNum;
	scanf("%d", &allKase);
	for(int kase = 1; kase <= allKase; kase++) {
		printf("Game %d: ", kase);
		scanf("%d", &edgeNum);
		int score = 0, now = 0, status = 0;
		for(int i = 0, u, v; i < edgeNum; i++) {
			scanf("%d%d", &u, &v);
			if(u > v) {
				swap(u, v);
			}
			status |= edgeID[pii(u, v)];
			int cnt = count(status, edgeID[pii(u, v)]);
			// 假如添加一边有得分，则可以继续再走一步，否则轮到对方走
			if(cnt)
				score += now == 0 ? cnt : -cnt;
			else
				now ^= 1;
		}
		printf("%c wins.\n", (now == 0 ? findMax(1, status, score) : findMin(-1, status, score)) > 0 ? 'A' : 'B');
	}

	return 0;
}
