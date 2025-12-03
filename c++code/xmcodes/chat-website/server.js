
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const path = require('path');
const { Pool } = require('pg');

if (process.env.NODE_ENV !== 'production') {
    require('dotenv').config();
}

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

// 数据库配置
const pool = new Pool({
    connectionString: process.env.DATABASE_URL,
    // 开发环境不需要 SSL
    ssl: process.env.NODE_ENV === 'production' ? { rejectUnauthorized: false } : false
});

// 添加数据库自动初始化函数
async function initializeDatabase() {
    try {
        await pool.query(`
      CREATE TABLE IF NOT EXISTS messages (
        id SERIAL PRIMARY KEY,
        username VARCHAR(50) DEFAULT '匿名用户',
        content TEXT NOT NULL,
        created_at TIMESTAMP WITH TIME ZONE DEFAULT NOW()
      );
      
      CREATE INDEX IF NOT EXISTS idx_messages_created_at ON messages(created_at);
    `);
        console.log('✅ 数据库表初始化完成');
    } catch (error) {
        console.error('❌ 数据库初始化失败:', error);
    }
}

// 中间件
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.json());

// 提供前端页面
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// API: 获取最近消息
app.get('/api/messages', async (req, res) => {
    try {
        const result = await pool.query(
            'SELECT id, username, content, created_at FROM messages WHERE created_at > NOW() - INTERVAL \'48 hours\' ORDER BY created_at ASC LIMIT 100'
        );
        res.json(result.rows);
    } catch (error) {
        console.error('Error fetching messages:', error);
        res.status(500).json({ error: 'Failed to fetch messages' });
    }
});

// Socket.IO 连接处理
io.on('connection', (socket) => {
    console.log('用户连接:', socket.id);

    // 处理新消息
    socket.on('sendMessage', async (data) => {
        try {
            const { username, content } = data;

            if (!content.trim()) return;

            // 插入消息到数据库
            const result = await pool.query(
                'INSERT INTO messages (username, content) VALUES ($1, $2) RETURNING id, username, content, created_at',
                [username || '匿名用户', content.trim()]
            );

            // 广播消息给所有客户端
            io.emit('newMessage', result.rows[0]);
        } catch (error) {
            console.error('Error saving message:', error);
            socket.emit('error', '消息发送失败');
        }
    });

    // 处理用户断开连接
    socket.on('disconnect', () => {
        console.log('用户断开连接:', socket.id);
    });
});

// 启动服务器
const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
    console.log(`服务器运行在端口 ${PORT}`);
});