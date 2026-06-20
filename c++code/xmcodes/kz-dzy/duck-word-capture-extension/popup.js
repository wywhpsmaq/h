document.addEventListener('DOMContentLoaded', function () {
    const startBtn = document.getElementById('startBtn');
    const stopBtn = document.getElementById('stopBtn');
    const clearBtn = document.getElementById('clearBtn');
    const exportBtn = document.getElementById('exportBtn');
    const wordCount = document.getElementById('wordCount');
    const wordList = document.getElementById('wordList');

    // 更新单词列表
    function updateWordList() {
        chrome.runtime.sendMessage({ action: 'getAllWords' }, function (response) {
            if (response && response.words) {
                const words = response.words;
                wordCount.textContent = words.length;

                // 显示单词列表
                wordList.innerHTML = '';
                words.slice(-10).reverse().forEach(item => {
                    const div = document.createElement('div');
                    div.className = 'word-item';
                    div.textContent = `${item.word} (${item.timestamp})`;
                    wordList.appendChild(div);
                });

                if (words.length === 0) {
                    wordList.innerHTML = '<div>暂无捕获的单词</div>';
                }
            }
        });
    }

    // 初始化
    updateWordList();
    setInterval(updateWordList, 1000);

    // 按钮事件
    startBtn.addEventListener('click', function () {
        chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
            if (tabs[0]) {
                chrome.tabs.sendMessage(tabs[0].id, { action: 'startCapture' });
                alert('开始捕获单词');
            }
        });
    });

    stopBtn.addEventListener('click', function () {
        chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
            if (tabs[0]) {
                chrome.tabs.sendMessage(tabs[0].id, { action: 'stopCapture' });
                alert('停止捕获单词');
            }
        });
    });

    clearBtn.addEventListener('click', function () {
        if (confirm('确定要清空所有单词吗？')) {
            chrome.runtime.sendMessage({ action: 'clearWords' }, function () {
                updateWordList();
                alert('已清空单词列表');
            });
        }
    });

    exportBtn.addEventListener('click', function () {
        chrome.runtime.sendMessage({ action: 'exportWords' }, function () {
            // 导出完成后会有提示
        });
    });
});