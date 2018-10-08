/********************************************************************************/
/* AC自动机：解决多个模式串匹配问题(Tested 9+ times)
 */
struct AC {
	int next[N][26], fail[N], idx, root, end[N]; // 可以修改下数组大小，以防MLE
	void init() {
		idx = 0;
		root = newNode();
	}
	int newNode() {
		for(int i = 0; i < 26; i++)
			next[idx][i] = -1;
		end[idx] = 0;
		return idx++;
	}
	void insert(char s[]) {
		int len = strlen(s), now = root;
		for(int i = 0; i < len; i++) {
			if(next[now][s[i] - 'a'] == -1)
				next[now][s[i] - 'a'] = newNode();
			now = next[now][s[i] - 'a'];
		}
		end[now]++;	//根据实际情况可能需要保存不同的信息
	}
	void build() {
		queue<int> que;
		fail[root] = root;
		for(int i = 0; i < 26; i++) {
			if(next[root][i] == -1) {
				next[root][i] = root;
			}
			else {
				fail[next[root][i]] = root;
				que.push(next[root][i]);
			}
		}
		while(que.size()) {
			int now = que.front();
			que.pop();
			for(int i = 0; i < 26; i++) {
				if(next[now][i] == -1) {
					next[now][i] = next[fail[now]][i];
				}
				else {
					fail[next[now][i]] = next[fail[now]][i];
					que.push(next[now][i]);
				}
			}
		}
	}
	int query(char s[]) {
		int ans = 0, len = strlen(s), now = root;
		for(int i = 0; i < len; i++) {
			now = next[now][s[i] - 'a'];
			int temp = now;
			while(temp != root) {
				ans += end[temp];
				end[temp] = 0;		//为避免重复统计，清零。必要时可以设置个flag数组。
				temp = fail[temp];
			}
		}
		return ans;
	}
	void debug() {
		printf("%37c", ' ');
		for(int i = 0; i < 26; i++)
			printf("%2c", i + 'a');
		printf("\n");
		for(int i = 0;i < idx;i++) {
			printf("id = %3d,fail = %3d,end = %3d,chi = [",i,fail[i],end[i]);
			for(int j = 0;j < 26;j++)
				printf("%2d",next[i][j]);
			printf("]\n");
		}
	}
}ac;
/********************************************************************************/
