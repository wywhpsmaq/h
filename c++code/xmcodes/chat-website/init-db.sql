-- 创建消息表
CREATE TABLE IF NOT EXISTS messages (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50) DEFAULT '匿名用户',
    content TEXT NOT NULL,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT NOW()
);

-- 创建索引以提高查询性能
CREATE INDEX IF NOT EXISTS idx_messages_created_at ON messages(created_at);

-- 可选：创建索引用于按时间范围查询
CREATE INDEX IF NOT EXISTS idx_messages_created_at_desc ON messages(created_at DESC);