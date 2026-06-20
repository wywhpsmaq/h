// 打字鸭单词捕获器 - 针对打字鸭游戏优化
class DuckWordCapture {
    constructor() {
        this.words = [];
        this.lastWord = '';
        this.isCapturing = true;

        console.log('打字鸭单词捕获器已加载');

        // 开始捕获
        this.startCapture();
    }

    startCapture() {
        // 方法1：监听键盘输入（主要方式）
        this.setupKeyboardListener();

        // 方法2：定期扫描游戏区域
        this.setupIntervalScanner();

        // 方法3：监听DOM变化
        this.setupMutationObserver();
    }

    // 监听键盘事件
    setupKeyboardListener() {
        document.addEventListener('keydown', (e) => {
            if (e.key === 'Enter' || e.key === ' ') {
                // 当用户按下回车或空格时，尝试捕获当前单词
                setTimeout(() => this.captureCurrentWord(), 100);
            }
        });
    }

    // 定期扫描游戏区域
    setupIntervalScanner() {
        setInterval(() => {
            this.captureCurrentWord();
        }, 500); // 每500毫秒检查一次
    }

    // 设置DOM变化监听
    setupMutationObserver() {
        const observer = new MutationObserver(() => {
            this.captureCurrentWord();
        });

        observer.observe(document.body, {
            childList: true,
            subtree: true,
            characterData: true
        });
    }

    // 捕获当前单词
    captureCurrentWord() {
        if (!this.isCapturing) return;

        // 尝试各种可能的选择器
        const selectors = [
            // 常见的游戏单词显示区域
            '.word-text', '.current-word', '.typing-text',
            '.game-text', '.text-display', '.target-word',
            '[class*="word"]', '[class*="text"]',
            '.duck-text', '.river-text',
            // 可能的ID
            '#currentWord', '#targetWord', '#gameWord'
        ];

        for (const selector of selectors) {
            const elements = document.querySelectorAll(selector);

            for (const element of elements) {
                const text = element.textContent || element.innerText || element.value;
                if (text && this.isValidWord(text)) {
                    this.processWord(text);
                    return; // 找到有效单词后返回
                }
            }
        }

        // 备用方法：查找所有文本节点
        this.findTextNodes();
    }

    // 查找文本节点
    findTextNodes() {
        const walker = document.createTreeWalker(
            document.body,
            NodeFilter.SHOW_TEXT,
            {
                acceptNode: function (node) {
                    const text = node.textContent.trim();
                    if (text && text.length > 2 && text.length < 15) {
                        return NodeFilter.FILTER_ACCEPT;
                    }
                    return NodeFilter.FILTER_SKIP;
                }
            }
        );

        let node;
        while (node = walker.nextNode()) {
            const text = node.textContent.trim();
            if (this.isValidWord(text)) {
                this.processWord(text);
                break;
            }
        }
    }

    // 验证单词
    isValidWord(text) {
        if (!text) return false;

        const cleanText = text.trim();

        // 排除条件
        if (cleanText.length < 2 || cleanText.length > 20) return false;
        if (cleanText.includes(' ')) return false; // 多个单词
        if (cleanText.includes('\n')) return false; // 换行符
        if (cleanText.includes('http')) return false; // URL
        if (/^\d+$/.test(cleanText)) return false; // 纯数字

        // 应该是字母单词
        if (!/^[a-zA-Z]+$/.test(cleanText)) return false;

        return true;
    }

    // 处理单词
    processWord(word) {
        const cleanWord = word.trim().toLowerCase();

        if (cleanWord &&
            cleanWord !== this.lastWord &&
            !this.words.includes(cleanWord)) {

            this.words.push(cleanWord);
            this.lastWord = cleanWord;

            console.log('捕获到单词:', cleanWord);

            // 发送到后台
            chrome.runtime.sendMessage({
                action: 'newWord',
                word: cleanWord
            });
        }
    }

    // 停止捕获
    stopCapture() {
        this.isCapturing = false;
    }
}

// 初始化
let wordCapture;

// 等待页面加载完成
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', () => {
        wordCapture = new DuckWordCapture();
    });
} else {
    wordCapture = new DuckWordCapture();
}

// 监听来自popup的消息
chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    if (request.action === 'getWords') {
        sendResponse({ words: wordCapture ? wordCapture.words : [] });
    } else if (request.action === 'startCapture') {
        if (wordCapture) wordCapture.isCapturing = true;
        sendResponse({ status: 'started' });
    } else if (request.action === 'stopCapture') {
        if (wordCapture) wordCapture.stopCapture();
        sendResponse({ status: 'stopped' });
    }
    return true;
});