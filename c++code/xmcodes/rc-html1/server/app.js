const express = require('express');
const cors = require('cors');
const cookieParser = require('cookie-parser');
const path = require('path');
const sequelize = require('./config/db');
const User = require('./models/User');
const Person = require('./models/Person');
const ActivityLog = require('./models/ActivityLog');

const authRoutes = require('./routes/auth');
const dataRoutes = require('./routes/data');
const adminRoutes = require('./routes/admin');

const app = express();
const PORT = process.env.PORT || 3000;

// 设置中间件
app.use(cors({
  origin: true,
  credentials: true
}));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, '../public')));

// 注册路由
app.use('/api/auth', authRoutes);
app.use('/api/data', dataRoutes);
app.use('/api/admin', adminRoutes);

// 主页路由
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, '../public/index.html'));
});

app.get('/main', (req, res) => {
  res.sendFile(path.join(__dirname, '../public/main.html'));
});

// 数据库同步和服务器启动
async function startServer() {
  try {
    // 同步数据库模型
    await sequelize.sync({
      alter: true,
      force: false
    });

    // 创建默认管理员用户（如果不存在）
    const adminUser = await User.findOne({ where: { username: 'admin' } });
    if (!adminUser) {
      await User.create({
        username: 'admin',
        password: 'admin123',
        isAdmin: true
      });
      console.log('默认管理员用户已创建: admin/admin123');
    }

    // 启动服务器
    app.listen(PORT, () => {
      console.log(`http://localhost:${PORT}`);
    });
  } catch (error) {
    console.error('启动服务器失败:', error);
    process.exit(1);
  }
}

startServer();