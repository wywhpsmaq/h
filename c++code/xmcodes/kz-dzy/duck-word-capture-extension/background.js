// 存储捕获的单词
let capturedWords = [];

// 监听来自内容脚本的消息
chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    if (request.action === 'newWord') {
        // 添加新单词
        if (!capturedWords.includes(request.word)) {
            capturedWords.push({
                word: request.word,
                timestamp: new Date().toLocaleString()
            });
            console.log('收到新单词:', request.word);
        }
        sendResponse({ received: true });
    }

    if (request.action === 'getAllWords') {
        sendResponse({ words: capturedWords });
    }

    if (request.action === 'clearWords') {
        capturedWords = [];
        sendResponse({ cleared: true });
    }

    if (request.action === 'exportWords') {
        exportWordsToFile();
        sendResponse({ exporting: true });
    }

    return true;
});

// 导出单词到文件
function exportWordsToFile() {
    if (capturedWords.length === 0) {
        alert('没有单词可导出');
        return;
    }

    // 创建CSV格式的内容
    let content = '单词,捕获时间\n';
    capturedWords.forEach(item => {
        content += `${item.word},${item.timestamp}\n`;
    });

    // 创建Blob对象
    const blob = new Blob([content], { type: 'text/csv;charset=utf-8;' });
    const url = URL.createObjectURL(blob);

    // 创建下载链接
    const link = document.createElement('a');
    link.href = url;
    const timestamp = new Date().toISOString().slice(0, 19).replace(/[:T]/g, '-');
    link.download = `typing-duck-words-${timestamp}.csv`;

    // 触发下载
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);

    console.log('单词已导出');
}

// 监听扩展安装
chrome.runtime.onInstalled.addListener(() => {
    console.log('打字鸭单词捕获器已安装');
});