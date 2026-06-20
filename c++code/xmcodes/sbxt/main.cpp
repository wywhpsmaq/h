//
// Created by wywhpsmaq on 2026/3/7.
//

#include "main.h"
#include <iostream>
#include <vector>
#include "tacl.h"
#include "htmlAPI.h"
int main() {
	//cs--------------------------
	freopen("cc.txt", "r", stdin);
	int n, m;
	char x;
	std::cin >> n >> m;
	std::vector<std::vector<int> > v;
	for (int i = 0; i < n; i++) {
		v.emplace_back();
		for (int j = 0; j < m; j++) {
			std::cin >> x;
			v[i].push_back((int)(x - '0'));
		}
	}
	v = txcl_sc(v);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << v[i][j];
		}
		std::cout << '\n';
	}
	if (generateImageFromMatrix(v, "output.png")) {
		std::cout << "成功生成图片" << std::endl;
	} else {
		std::cerr << "生成图片失败" << std::endl;
	}
	//cs--------------------------
}
