#zsd 
在C++信息竞赛里，标准模板库（STL）容器发挥着关键作用，能让代码更简洁、高效。下面是对常用STL容器知识点的详细总结：

### 序列式容器
#### 1. `vector`
- **特点**：动态数组，能在末尾高效地添加或删除元素，支持随机访问。
- **使用示例**：
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `push_back()`：在末尾添加元素。
    - `pop_back()`：删除末尾元素。
    - `size()`：返回元素数量。
    - `empty()`：判断容器是否为空。

#### 2. `deque`
- **特点**：双端队列，可在头部和尾部高效地添加或删除元素，也支持随机访问。
- **使用示例**：
```cpp
#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq;
    dq.push_back(1);
    dq.push_front(0);
    dq.push_back(2);

    for (int i = 0; i < dq.size(); ++i) {
        std::cout << dq[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `push_back()`：在末尾添加元素。
    - `push_front()`：在头部添加元素。
    - `pop_back()`：删除末尾元素。
    - `pop_front()`：删除头部元素。

#### 3. `list`
- **特点**：双向链表，能在任意位置高效地插入或删除元素，但不支持随机访问。
- **使用示例**：
```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `push_back()`：在末尾添加元素。
    - `push_front()`：在头部添加元素。
    - `pop_back()`：删除末尾元素。
    - `pop_front()`：删除头部元素。
    - `insert()`：在指定位置插入元素。
    - `erase()`：删除指定位置的元素。

### 关联式容器
#### 1. `set`
- **特点**：集合，元素唯一且自动排序。
- **使用示例**：
```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s;
    s.insert(3);
    s.insert(1);
    s.insert(2);

    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `insert()`：插入元素。
    - `erase()`：删除元素。
    - `find()`：查找元素，返回迭代器。
    - `count()`：返回元素的数量（0 或 1）。

#### 2. `multiset`
- **特点**：与 `set` 类似，但允许有重复元素，元素同样自动排序。
- **使用示例**：
```cpp
#include <iostream>
#include <set>

int main() {
    std::multiset<int> ms;
    ms.insert(3);
    ms.insert(1);
    ms.insert(2);
    ms.insert(2);

    for (auto it = ms.begin(); it != ms.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：与 `set` 类似。

#### 3. `map`
- **特点**：键值对集合，键唯一且自动排序。
- **使用示例**：
```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> m;
    m["apple"] = 1;
    m["banana"] = 2;
    m["cherry"] = 3;

    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    return 0;
}
```
- **常用方法**：
    - `insert()`：插入键值对。
    - `erase()`：删除指定键的元素。
    - `find()`：查找指定键的元素，返回迭代器。
    - `count()`：返回指定键的元素数量（0 或 1）。

#### 4. `multimap`
- **特点**：与 `map` 类似，但允许有重复的键，键同样自动排序。
- **使用示例**：
```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::multimap<std::string, int> mm;
    mm.insert(std::make_pair("apple", 1));
    mm.insert(std::make_pair("banana", 2));
    mm.insert(std::make_pair("apple", 3));

    for (auto it = mm.begin(); it != mm.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    return 0;
}
```
- **常用方法**：与 `map` 类似。

### 容器适配器
#### 1. `stack`
- **特点**：栈，遵循后进先出（LIFO）原则。
- **使用示例**：
```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);

    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `push()`：入栈。
    - `pop()`：出栈。
    - `top()`：返回栈顶元素。
    - `empty()`：判断栈是否为空。
    - `size()`：返回栈中元素数量。

#### 2. `queue`
- **特点**：队列，遵循先进先出（FIFO）原则。
- **使用示例**：
```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `push()`：入队。
    - `pop()`：出队。
    - `front()`：返回队首元素。
    - `back()`：返回队尾元素。
    - `empty()`：判断队列是否为空。
    - `size()`：返回队列中元素数量。

#### 3. `priority_queue`
- **特点**：优先队列，元素按优先级排序，默认最大元素在队首。
- **使用示例**：
```cpp
#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> pq;
    pq.push(3);
    pq.push(1);
    pq.push(2);

    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;

    return 0;
}
```
- **常用方法**：
    - `push()`：插入元素。
    - `pop()`：删除队首元素。
    - `top()`：返回队首元素。
    - `empty()`：判断队列是否为空。
    - `size()`：返回队列中元素数量。

这些STL容器在信息竞赛中能极大地提升编程效率，你要根据具体问题选择合适的容器。 