const { Pool } = require('pg');

// 加载环境变量（开发环境）
if (process.env.NODE_ENV !== 'production') {
    require('dotenv').config();
}

// 数据库配置
const pool = new Pool({
    connectionString: process.env.DATABASE_URL,
    ssl: process.env.NODE_ENV === 'production' ? { rejectUnauthorized: false } : false
});

async function cleanupOldMessages() {
    try {
        const result = await pool.query(
            "DELETE FROM messages WHERE created_at < NOW() - INTERVAL '48 hours'"
        );

        console.log(`[${new Date().toISOString()}] 已清理 ${result.rowCount} 条超过48小时的消息`);

        await pool.end();
        process.exit(0);
    } catch (error) {
        console.error('清理消息时出错:', error);
        process.exit(1);
    }
}

cleanupOldMessages();