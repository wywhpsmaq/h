const express = require('express');
const cors = require('cors');
const cookieParser = require('cookie-parser');
const path = require('path');
const { DataTypes } = require('sequelize');
const sequelize = require('./config/db');
const User = require('./models/User');
const Person = require('./models/Person');
const ActivityLog = require('./models/ActivityLog');
const LoginAudit = require('./models/LoginAudit');

const authRoutes = require('./routes/auth');
const dataRoutes = require('./routes/data');
const adminRoutes = require('./routes/admin');

require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 3000;

app.set('trust proxy' , 1);

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

// 数据库同步和服务器启�����
async function startServer() {
  try {
    // 同步数据库模型
    await sequelize.sync({
      alter: true,
      force: false
    });
    await ensureUserSchema();

    // 创建默认管理员用户（如果不存在）
    const adminUser = await User.findOne({ where: { username: 'admin' } });
    if (!adminUser) {
      await User.create({
        username: 'admin',
        email: 'admin@local.test',
        password: 'admin123',
        isAdmin: true,
        permissions: require('./models/User').buildAdminPermissions()
      });
      console.log('默认管理员用户已创建: admin/admin123');
    } else {
      await ensureAdminPermissions();
    }

    const legacyUsers = await User.findAll({ where: { email: null } });
    for (const legacyUser of legacyUsers) {
      await legacyUser.update({ email: `legacy-user-${legacyUser.id}@local.test` });
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

async function ensureAdminPermissions() {
  const adminUser = await User.findOne({ where: { username: 'admin' } });
  if (adminUser) {
    const basePermissions = require('./models/User').buildAdminPermissions();
    const existingPermissions = adminUser.permissions || {};
    const mergedPermissions = {
      ...basePermissions,
      ...existingPermissions,
      dataManagement: { ...basePermissions.dataManagement, ...(existingPermissions.dataManagement || {}) },
      changeInfo: { ...basePermissions.changeInfo, ...(existingPermissions.changeInfo || {}) },
      enterAdmin: { ...basePermissions.enterAdmin, ...(existingPermissions.enterAdmin || {}) },
      userManagement: { ...basePermissions.userManagement, ...(existingPermissions.userManagement || {}) },
      registrationManagement: { ...basePermissions.registrationManagement, ...(existingPermissions.registrationManagement || {}) }
    };

    Object.keys(mergedPermissions).forEach(groupKey => {
      const group = mergedPermissions[groupKey] || {};
      if (group && typeof group === 'object') {
        group.enabled = true;
        Object.keys(group).forEach(key => {
          if (typeof group[key] === 'boolean') {
            group[key] = true;
          }
        });
      }
    });

    if (!adminUser.permissions || JSON.stringify(adminUser.permissions) !== JSON.stringify(mergedPermissions)) {
      await adminUser.update({ permissions: mergedPermissions, isAdmin: true });
    } else if (!adminUser.isAdmin) {
      await adminUser.update({ isAdmin: true });
    }
  }
}

async function ensureUserSchema() {
  try {
    const table = await sequelize.getQueryInterface().describeTable('users');
    if (!table.permissions) {
      await sequelize.getQueryInterface().addColumn('users', 'permissions', {
        type: DataTypes.JSON,
        allowNull: true,
        defaultValue: require('./models/User').defaultPermissions
      });
      console.log('已补齐 users.permissions 列');
    }
  } catch (error) {
    if (!/does not exist|不存在/i.test(error.message || '')) {
      console.warn('检查 users 表结构失败:', error.message);
    }
  }
}

startServer();