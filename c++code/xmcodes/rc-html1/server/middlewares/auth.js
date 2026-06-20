const jwt = require('jsonwebtoken');
const jwtConfig = require('../config/jwt');
const User = require('../models/User');
const ActivityLog = require('../models/ActivityLog');

const auth = async (req, res, next) => {
  try {
    const token = req.header('Authorization')?.replace('Bearer ', '') || req.cookies.token;
    if (!token) {
      throw new Error('未提供认证令牌');
    }

    const decoded = jwt.verify(token, jwtConfig.secret);
    const user = await User.findByPk(decoded.id);
    if (!user) {
      throw new Error('用户不存在');
    }

    // 检查用户是否被封禁
    if (user.isBanned) {
      throw new Error('用户已被封禁');
    }

    req.user = user;
    req.token = token;
    next();
  } catch (error) {
    res.status(401).json({ error: error.message || '认证失败，请重新登录' });
  }
};

const adminAuth = async (req, res, next) => {
  try {
    await auth(req, res, () => {});
    if (!req.user.isAdmin) {
      throw new Error('没有管理员权限');
    }
    next();
  } catch (error) {
    res.status(403).json({ error: error.message || '没有权限访问此资源' });
  }
};

// 终极管理员权限（仅admin用户）
const ultimateAdminAuth = async (req, res, next) => {
  try {
    await auth(req, res, () => {});
    if (!req.user.isAdmin || req.user.username !== 'admin') {
      throw new Error('只有终极管理员才有权限执行此操作');
    }
    next();
  } catch (error) {
    res.status(403).json({ error: error.message || '没有权限访问此资源' });
  }
};

const logActivity = async (req, res, next) => {
  if (req.user) {
    try {
      await ActivityLog.create({
        userId: req.user.id,
        username: req.user.username,
        action: req.method + ' ' + req.path,
        description: JSON.stringify(req.body),
        ipAddress: req.ip,
        userAgent: req.headers['user-agent']
      });
    } catch (logError) {
      console.error('日志记录失败:', logError);
    }
  }
  next();
};

module.exports = { auth, adminAuth, ultimateAdminAuth, logActivity };