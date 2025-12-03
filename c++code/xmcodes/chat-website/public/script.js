class ChatApp {
    constructor() {
        this.socket = io();
        this.messages = [];
        this.onlineCount = 0;

        this.initializeElements();
        this.setupEventListeners();
        this.loadPreviousMessages();
    }

    initializeElements() {
        this.messagesContainer = document.getElementById('messages');
        this.messageInput = document.getElementById('messageInput');
        this.sendButton = document.getElementById('sendButton');
        this.usernameInput = document.getElementById('username');
        this.onlineCountElement = document.getElementById('onlineCount');
    }

    setupEventListeners() {
        // 发送消息
        this.sendButton.addEventListener('click', () => this.sendMessage());
        this.messageInput.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.sendMessage();
        });

        // Socket.IO 事件监听
        this.socket.on('newMessage', (message) => {
            this.addMessage(message);
        });

        this.socket.on('userCount', (count) => {
            this.updateOnlineCount(count);
        });

        this.socket.on('error', (error) => {
            this.showSystemMessage(`错误: ${error}`);
        });
    }

    async loadPreviousMessages() {
        try {
            const response = await fetch('/api/messages');
            const messages = await response.json();

            this.messagesContainer.innerHTML = '';
            messages.forEach(message => this.addMessage(message, false));

            this.scrollToBottom();
        } catch (error) {
            console.error('加载消息失败:', error);
            this.showSystemMessage('加载历史消息失败');
        }
    }

    sendMessage() {
        const content = this.messageInput.value.trim();
        const username = this.usernameInput.value.trim();

        if (!content) return;

        this.socket.emit('sendMessage', {
            username: username || '匿名用户',
            content: content
        });

        this.messageInput.value = '';
        this.messageInput.focus();
    }

    addMessage(message, animate = true) {
        const messageElement = document.createElement('div');
        messageElement.className = 'message';

        if (!animate) {
            messageElement.style.animation = 'none';
        }

        const timestamp = new Date(message.created_at).toLocaleString('zh-CN');

        messageElement.innerHTML = `
            <div class="message-header">
                <span class="username">${this.escapeHtml(message.username)}</span>
                <span class="timestamp">${timestamp}</span>
            </div>
            <div class="message-content">${this.escapeHtml(message.content)}</div>
        `;

        this.messagesContainer.appendChild(messageElement);
        this.scrollToBottom();
    }

    showSystemMessage(content) {
        const messageElement = document.createElement('div');
        messageElement.className = 'system-message';
        messageElement.textContent = content;
        this.messagesContainer.appendChild(messageElement);
        this.scrollToBottom();
    }

    updateOnlineCount(count) {
        this.onlineCount = count;
        this.onlineCountElement.textContent = count;
    }

    scrollToBottom() {
        this.messagesContainer.scrollTop = this.messagesContainer.scrollHeight;
    }

    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }
}

// 初始化聊天应用
document.addEventListener('DOMContentLoaded', () => {
    new ChatApp();
});