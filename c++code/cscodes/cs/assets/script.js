class MaxHeap {
    constructor() {
        this.heap = [null]; // 1-based indexing, index 0 is placeholder
        this.cnt = 0;
        this.animationSpeed = 700; // Slower default for beginners
        this.isAnimating = false;
        this.teachingMode = false; // Teaching mode flag
        this.nextStepResolver = null; // For step-by-step wait
    }

    // --- Helper Helpers ---
    getParentIndex(i) { return Math.floor(i / 2); }
    getLeftChildIndex(i) { return 2 * i; }
    getRightChildIndex(i) { return 2 * i + 1; }

    // --- Teaching Mode Helpers ---
    showExplanation(text) {
        const el = document.getElementById('explanation-text');
        if (el) el.innerText = text;
    }

    async waitForNextStep() {
        if (!this.teachingMode) return;

        // Show next-step button
        const container = document.getElementById('next-step-container');
        if (container) container.style.display = 'block';

        // Wait for user to click
        await new Promise(resolve => {
            this.nextStepResolver = resolve;
        });

        // Hide button after click
        if (container) container.style.display = 'none';
    }

    async insert(value) {
        if (this.cnt >= 31) {
            showToast("堆已满 (演示仅限31个节点)", "error");
            return;
        }

        this.showExplanation(`📥 开始插入数字 ${value}...`);
        await this.waitForNextStep();

        // Highlight Code: Insert Start
        this.highlightCode('line-add');
        await this.wait(200);

        this.cnt++;
        this.heap[this.cnt] = value;
        this.highlightCode('line-add-push');

        this.showExplanation(`✅ 把 ${value} 放到数组末尾，位置 h[${this.cnt}]`);
        await this.render();
        await this.highlightNode(this.cnt, 'success'); // Highlight new node
        await this.waitForNextStep();

        this.highlightCode('line-add-up');
        this.showExplanation(`⬆️ 现在检查是否需要"上浮"...`);
        await this.waitForNextStep();

        await this.up(this.cnt);

        this.highlightCode('line-add-end');
        await this.wait(200);
        this.clearCodeHighlight();
        this.showExplanation(`🎉 插入完成！数字 ${value} 已经在正确的位置了。`);
        await this.render();
    }

    async extractMax() {
        if (this.cnt === 0) {
            showToast("堆是空的", "error");
            return;
        }

        const max = this.heap[1];
        this.showExplanation(`📤 开始取出最大值：${max}（根节点）`);
        await this.waitForNextStep();

        // We simulate the 'pop' logic: print top, swap/replace top with last, then down
        this.highlightCode('line-print');
        await this.wait(200);

        // Highlight root to be removed
        await this.highlightNode(1, 'danger');

        this.highlightCode('line-swap-pop');
        if (this.cnt === 1) {
            this.cnt = 0;
            this.heap.pop(); // Remove 1
            await this.render();
            this.clearCodeHighlight();
            this.showExplanation(`🎉 取出完成！最大值是 ${max}`);
            return max;
        }

        this.showExplanation(`🔄 把最后一个数字 ${this.heap[this.cnt]} 移到根节点位置`);
        await this.waitForNextStep();

        // Move last to root
        await this.swapVisual(1, this.cnt);
        this.heap[1] = this.heap.pop();
        this.cnt--;

        await this.render();

        this.highlightCode('line-main-down');
        this.showExplanation(`⬇️ 现在检查是否需要"下沉"...`);
        await this.waitForNextStep();

        await this.down(1);

        this.highlightCode('line-while-end'); // End of one iteration
        await this.wait(200);
        this.clearCodeHighlight();
        this.showExplanation(`🎉 取出完成！最大值是 ${max}`);

        await this.render();
        return max;
    }

    // --- Core Logic with Animation Hooks ---
    async up(u) {
        this.highlightCode('line-up-sig');

        while (true) {
            this.highlightCode('line-up-while');
            const p = Math.floor(u / 2);

            if (p > 0) {
                this.showExplanation(`🔍 比较 h[${u}]=${this.heap[u]} 和它的父亲 h[${p}]=${this.heap[p]}`);
                await this.highlightComparison(u, p);
                if (this.heap[p] < this.heap[u]) {
                    this.showExplanation(`⬆️ ${this.heap[u]} > ${this.heap[p]}，需要交换！孩子比父亲大，要上浮`);
                    await this.waitForNextStep();

                    // Swap Data
                    [this.heap[u], this.heap[p]] = [this.heap[p], this.heap[u]];

                    // Visualize Swap
                    this.highlightCode('line-up-swap');
                    await this.swapVisual(u, p);

                    // Update u to parent position and show current position
                    this.highlightCode('line-up-move');
                    u = p;

                    // Visual: highlight current position (we moved up!)
                    this.showExplanation(`📍 现在 u = ${u}，继续往上检查...`);
                    await this.highlightNode(u, 'success');
                } else {
                    this.showExplanation(`✅ ${this.heap[u]} ≤ ${this.heap[p]}，不需要交换了，位置正确！`);
                    break;
                }
            } else {
                this.showExplanation(`✅ 已经到达根节点，上浮完成！`);
                break;
            }
        }
        this.highlightCode('line-up-end');
    }

    async down(u) {
        this.highlightCode('line-down-sig');

        this.highlightCode('line-down-t');
        let t = u;
        this.showExplanation(`🔍 检查位置 ${u} 的节点（值=${this.heap[u]}）和它的孩子们`);
        await this.wait();

        const l = 2 * u;
        const r = 2 * u + 1;

        this.highlightCode('line-down-check-l');
        if (l <= this.cnt) {
            this.showExplanation(`👈 看左孩子 h[${l}]=${this.heap[l]}，当前最大是 h[${t}]=${this.heap[t]}`);
            await this.highlightComparison(l, t);
            if (this.heap[l] > this.heap[t]) {
                t = l;
                this.showExplanation(`📌 左孩子 ${this.heap[l]} 更大，记住它的位置`);
            }
        }

        this.highlightCode('line-down-check-r');
        if (r <= this.cnt) {
            this.showExplanation(`👉 看右孩子 h[${r}]=${this.heap[r]}，当前最大是 h[${t}]=${this.heap[t]}`);
            // Note: t might have updated to l, so we compare r with current t
            await this.highlightComparison(r, t);
            if (this.heap[r] > this.heap[t]) {
                t = r;
                this.showExplanation(`📌 右孩子 ${this.heap[r]} 更大，记住它的位置`);
            }
        }

        this.highlightCode('line-down-check-swap');
        if (u !== t) {
            this.showExplanation(`⬇️ 孩子 ${this.heap[t]} 比父亲 ${this.heap[u]} 大，需要交换！`);
            await this.waitForNextStep();

            // Swap Data
            [this.heap[u], this.heap[t]] = [this.heap[t], this.heap[u]];

            this.highlightCode('line-down-swap');
            await this.swapVisual(u, t);

            this.highlightCode('line-down-recurse');
            this.showExplanation(`🔄 继续检查交换后的位置 ${t}...`);
            await this.down(t);
        } else {
            this.showExplanation(`✅ 没有孩子比父亲大，下沉完成！位置正确！`);
            this.highlightCode('line-down-end');
        }
    }

    // --- Visualization & Animation ---

    async highlightNode(index, type = 'highlight') {
        const node = document.getElementById(`node-${index}`);
        const arrayItem = document.getElementById(`array-item-${index}`);
        if (node) node.classList.add(type);
        if (arrayItem) arrayItem.classList.add(type);

        await this.wait();

        if (node) node.classList.remove(type);
        if (arrayItem) arrayItem.classList.remove(type);
    }

    async highlightComparison(idx1, idx2) {
        const node1 = document.getElementById(`node-${idx1}`);
        const node2 = document.getElementById(`node-${idx2}`);
        if (node1) node1.classList.add('highlight');
        if (node2) node2.classList.add('highlight');

        await this.wait();

        if (node1) node1.classList.remove('highlight');
        if (node2) node2.classList.remove('highlight');
    }

    async swapVisual(idx1, idx2) {
        const node1 = document.getElementById(`node-${idx1}`);
        const node2 = document.getElementById(`node-${idx2}`);
        const arr1 = document.getElementById(`array-item-${idx1}`);
        const arr2 = document.getElementById(`array-item-${idx2}`);

        if (!node1 || !node2) return;

        // Read current displayed values (before visual update)
        const displayedVal1 = node1.innerText;
        const displayedVal2 = node2.innerText;

        // The heap array already has swapped data, so:
        // - newVal for position idx1 is this.heap[idx1] (which was originally at idx2)
        // - newVal for position idx2 is this.heap[idx2] (which was originally at idx1)
        const newVal1 = this.heap[idx1]; // Value that should end up at idx1
        const newVal2 = this.heap[idx2]; // Value that should end up at idx2

        // Step 1: Highlight both nodes - "we're about to swap these!"
        node1.classList.add('highlight');
        node2.classList.add('highlight');
        if (arr1) arr1.classList.add('highlight');
        if (arr2) arr2.classList.add('highlight');

        await this.wait(this.animationSpeed * 0.5);

        // Step 2: Scale down (values "disappear")
        node1.style.transition = 'transform 0.2s ease-in';
        node2.style.transition = 'transform 0.2s ease-in';
        node1.style.transform = 'scale(0.5)';
        node2.style.transform = 'scale(0.5)';

        await new Promise(r => setTimeout(r, 200));

        // Step 3: Update values
        node1.innerText = newVal1;
        node2.innerText = newVal2;

        // Update array view
        if (arr1 && arr2) {
            arr1.innerHTML = `${newVal1}<span class="index-label">${idx1}</span>`;
            arr2.innerHTML = `${newVal2}<span class="index-label">${idx2}</span>`;
        }

        // Step 4: Scale back up with new values (values "appear")
        node1.style.transition = 'transform 0.2s ease-out';
        node2.style.transition = 'transform 0.2s ease-out';
        node1.style.transform = 'scale(1.15)';
        node2.style.transform = 'scale(1.15)';

        await new Promise(r => setTimeout(r, 200));

        // Step 5: Return to normal
        node1.style.transform = '';
        node2.style.transform = '';
        node1.style.transition = '';
        node2.style.transition = '';

        // Remove highlights
        node1.classList.remove('highlight');
        node2.classList.remove('highlight');
        if (arr1) arr1.classList.remove('highlight');
        if (arr2) arr2.classList.remove('highlight');

        await this.wait(this.animationSpeed * 0.3);
    }

    highlightCode(id) {
        // Map ids to tabs to auto-switch
        const tabMap = {
            'line-const': 'tab-template',
            'line-global': 'tab-template',
            'line-main': 'tab-template',
            'line-main-brace': 'tab-template',
            'line-io': 'tab-template',
            'line-loop': 'tab-template',
            'line-cnt': 'tab-template',
            'line-build': 'tab-template',
            'line-while': 'tab-template',
            'line-while-brace': 'tab-template',
            'line-print': 'tab-template',
            'line-swap-pop': 'tab-template',
            'line-main-down': 'tab-template',
            'line-while-end': 'tab-template',

            'line-up-sig': 'tab-up',
            'line-up-brace': 'tab-up',
            'line-up-while': 'tab-up',
            'line-up-while-brace': 'tab-up',
            'line-up-swap': 'tab-up',
            'line-up-move': 'tab-up',
            'line-up-while-end': 'tab-up',
            'line-up-end': 'tab-up',
            'line-add': 'tab-up',
            'line-add-brace': 'tab-up',
            'line-add-push': 'tab-up',
            'line-add-up': 'tab-up',
            'line-add-end': 'tab-up',

            'line-down-sig': 'tab-down',
            'line-down-brace': 'tab-down',
            'line-down-t': 'tab-down',
            'line-down-check-l': 'tab-down',
            'line-down-check-r': 'tab-down',
            'line-down-check-swap': 'tab-down',
            'line-down-if-brace': 'tab-down',
            'line-down-swap': 'tab-down',
            'line-down-recurse': 'tab-down',
            'line-down-if-end': 'tab-down',
            'line-down-end': 'tab-down'
        };

        const targetTab = tabMap[id];
        if (targetTab) {
            this.switchTab(targetTab);
        }

        // Remove active class from all lines
        document.querySelectorAll('.code-line').forEach(el => el.classList.remove('active'));

        const line = document.getElementById(id);
        if (line) {
            line.classList.add('active');
            line.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
        }
    }

    switchTab(tabId) {
        // UI Tab Switch
        document.querySelectorAll('.tab-btn').forEach(b => {
            b.classList.remove('active');
            if (b.dataset.tab === tabId) b.classList.add('active');
        });

        document.querySelectorAll('.code-tab-content').forEach(c => {
            c.classList.remove('active');
        });

        const content = document.getElementById(tabId);
        if (content) content.classList.add('active');
    }

    clearCodeHighlight() {
        document.querySelectorAll('.code-line').forEach(el => el.classList.remove('active'));
    }

    async wait(ms) {
        const t = ms || this.animationSpeed;
        return new Promise(resolve => setTimeout(resolve, t));
    }

    async render() {
        const container = document.getElementById('tree-container');
        const connectionsLayer = document.getElementById('connections-layer');
        const arrayView = document.getElementById('array-view');

        // Remove existing nodes (keep SVG layer)
        const existingNodes = container.querySelectorAll('.node');
        existingNodes.forEach(n => n.remove());

        connectionsLayer.innerHTML = '';
        arrayView.innerHTML = '';

        if (this.cnt === 0) return;

        const containerWidth = container.offsetWidth;
        const levelHeight = 70;

        // Loop from 1 to cnt (1-based)
        for (let index = 1; index <= this.cnt; index++) {
            const value = this.heap[index];
            const level = Math.floor(Math.log2(index));
            const levelIndex = index - Math.pow(2, level);

            // Adjust section width based on level to prevent overlap
            // 2^level sections at this level
            const sections = Math.pow(2, level);
            const sectionWidth = containerWidth / sections;

            // Center in section
            const x = (sectionWidth * levelIndex) + (sectionWidth / 2) - 22; // -22 for half node width
            const y = level * levelHeight + 50;

            const node = document.createElement('div');
            node.className = 'node';
            node.id = `node-${index}`;
            node.innerText = value;
            node.style.left = `${x}px`;
            node.style.top = `${y}px`;
            container.appendChild(node);

            if (index > 1) {
                const parentIndex = this.getParentIndex(index);
                const parentNode = document.getElementById(`node-${parentIndex}`);
                if (parentNode) {
                    const pX = parseFloat(parentNode.style.left) + 25;
                    const pY = parseFloat(parentNode.style.top) + 25;
                    const cX = x + 25;
                    const cY = y + 25;

                    const line = document.createElementNS('http://www.w3.org/2000/svg', 'line');
                    line.setAttribute('x1', pX);
                    line.setAttribute('y1', pY);
                    line.setAttribute('x2', cX);
                    line.setAttribute('y2', cY);
                    line.setAttribute('stroke', '#475569');
                    line.setAttribute('stroke-width', '2');
                    connectionsLayer.appendChild(line);
                }
            }

            const arrayItem = document.createElement('div');
            arrayItem.className = 'array-item';
            arrayItem.id = `array-item-${index}`;
            arrayItem.innerHTML = `${value}<span class="index-label">${index}</span>`;
            arrayView.appendChild(arrayItem);
        }
    }
}

// Global App State
const heapApp = new MaxHeap();

document.addEventListener('DOMContentLoaded', () => {
    heapApp.render();

    document.getElementById('insert-btn').addEventListener('click', async () => {
        if (heapApp.isAnimating) return;
        const input = document.getElementById('value-input');
        const val = parseInt(input.value);
        if (!isNaN(val)) {
            lockUI();
            await heapApp.insert(val);
            unlockUI();
            input.value = '';
            input.focus();
        }
    });

    document.getElementById('extract-max-btn').addEventListener('click', async () => {
        if (heapApp.isAnimating) return;
        lockUI();
        const max = await heapApp.extractMax();
        if (max !== undefined) {
            showToast(`取出最大值: ${max}`, 'success');
        }
        unlockUI();
    });

    document.getElementById('randomize-btn').addEventListener('click', async () => {
        if (heapApp.isAnimating) return;
        lockUI();
        heapApp.heap = [null]; // Reset with placeholder
        heapApp.cnt = 0;

        const tempArr = [];
        for (let i = 0; i < 15; i++) {
            tempArr.push(Math.floor(Math.random() * 100) + 1);
        }

        // Build heap properly (1-based)
        // Just fill and then heapify for correct demo?
        // Or standard O(n) build
        for (let x of tempArr) {
            heapApp.heap.push(x);
            heapApp.cnt++;
        }

        for (let i = Math.floor(heapApp.cnt / 2); i >= 1; i--) {
            await manualDown(heapApp.heap, i, heapApp.cnt);
        }

        await heapApp.render();
        unlockUI();
    });

    document.getElementById('clear-btn').addEventListener('click', async () => {
        if (heapApp.isAnimating) return;
        heapApp.heap = [null];
        heapApp.cnt = 0;
        await heapApp.render();
        document.getElementById('value-input').value = '';
    });

    const speedSlider = document.getElementById('speed-slider');
    speedSlider.addEventListener('input', (e) => {
        const val = parseInt(e.target.value);
        heapApp.animationSpeed = 1100 - (val * 100);
    });

    // Manual Tab Switching
    document.querySelectorAll('.tab-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            if (heapApp.isAnimating) return;
            heapApp.switchTab(btn.dataset.tab);
        });
    });
});

// Helper for randomize (non-visual)
async function manualDown(arr, i, n) {
    let t = i;
    if (2 * i <= n && arr[2 * i] > arr[t]) t = 2 * i;
    if (2 * i + 1 <= n && arr[2 * i + 1] > arr[t]) t = 2 * i + 1;
    if (i !== t) {
        [arr[i], arr[t]] = [arr[t], arr[i]];
        await manualDown(arr, t, n);
    }
}

function lockUI() {
    heapApp.isAnimating = true;
    document.querySelectorAll('button').forEach(b => {
        // Don't disable the next-step button - it needs to work during animation
        if (b.id !== 'next-step-btn') {
            b.disabled = true;
        }
    });
    document.getElementById('value-input').disabled = true;
    document.getElementById('speed-slider').disabled = true;
}

function unlockUI() {
    heapApp.isAnimating = false;
    document.querySelectorAll('button').forEach(b => b.disabled = false);
    document.getElementById('value-input').disabled = false;
    document.getElementById('speed-slider').disabled = false;
    document.getElementById('value-input').focus();
}

function showToast(msg, type = 'info') {
    const container = document.getElementById('toast-container');
    const toast = document.createElement('div');
    toast.className = `toast ${type}`;
    toast.innerText = msg;
    container.appendChild(toast);
    setTimeout(() => toast.remove(), 3000);
}

// Knowledge Card Toggle
function toggleKnowledge() {
    const content = document.getElementById('card-content');
    const icon = document.getElementById('toggle-icon');
    if (content && icon) {
        content.classList.toggle('collapsed');
        icon.classList.toggle('collapsed');
    }
}

// Teaching Mode Toggle Event
document.addEventListener('DOMContentLoaded', () => {
    const teachingToggle = document.getElementById('teaching-mode-toggle');
    if (teachingToggle) {
        teachingToggle.addEventListener('change', (e) => {
            heapApp.teachingMode = e.target.checked;
            if (e.target.checked) {
                heapApp.showExplanation('📖 教学模式已开启！每个步骤都会等你点击"下一步"');
            } else {
                heapApp.showExplanation('点击下方按钮开始操作...');
            }
        });
    }

    const nextStepBtn = document.getElementById('next-step-btn');
    if (nextStepBtn) {
        nextStepBtn.addEventListener('click', () => {
            if (heapApp.nextStepResolver) {
                heapApp.nextStepResolver();
                heapApp.nextStepResolver = null;
            }
        });
    }
});
