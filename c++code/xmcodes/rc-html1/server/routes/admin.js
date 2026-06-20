const express = require('express');
const crypto = require('crypto');
const User = require('../models/User');
const ActivityLog = require('../models/ActivityLog');
const RegistrationToken = require('../models/RegistrationToken');
const { adminAuth, ultimateAdminAuth } = require('../middlewares/auth');

const router = express.Router();

// 获取所有用户
router.get('/users', adminAuth, async (req, res) => {
  try {
    const users = await User.findAll({ attributes: ['id', 'username', 'isAdmin', 'isBanned', 'lastLogin', 'createdAt', 'updatedAt'] });
    res.json(users);
  } catch (error) {
    res.status(500).json({ error: '获取用户列表失败', message: error.message });
  }
});

// 创建新用户
router.post('/users', adminAuth, async (req, res) => {
  try {
    const { username, password, isAdmin } = req.body;

    if (!username || !password) {
      return res.status(400).json({ error: '请提供用户名和密码' });
    }

    const user = await User.create({ username, password, isAdmin });
    res.status(201).json(user);
  } catch (error) {
    res.status(500).json({ error: '创建用户失败', message: error.message });
  }
});

// 删除用户（仅终极管理员）
router.delete('/users/:id', ultimateAdminAuth, async (req, res) => {
  try {
    const user = await User.findByPk(req.params.id);

    if (!user) {
      return res.status(404).json({ error: '用户不存在' });
    }

    // 禁止删除admin用户
    if (user.username === 'admin') {
      return res.status(403).json({ error: '不能删除管理员账户' });
    }

    await user.destroy();
    res.json({ message: '删除用户成功' });
  } catch (error) {
    res.status(500).json({ error: '删除用户失败', message: error.message });
  }
});

// 封禁/解封用户（仅终极管理员）
router.put('/users/:id/ban', ultimateAdminAuth, async (req, res) => {
  try {
    const { isBanned } = req.body;
    const user = await User.findByPk(req.params.id);

    if (!user) {
      return res.status(404).json({ error: '用户不存在' });
    }

    // 禁止封禁admin用户
    if (user.username === 'admin') {
      return res.status(403).json({ error: '不能封禁管理员账户' });
    }

    await user.update({ isBanned });
    res.json({ message: isBanned ? '用户已封禁' : '用户已解封' });
  } catch (error) {
    res.status(500).json({ error: '更新用户状态失败', message: error.message });
  }
});

// 获取活动日志
router.get('/logs', adminAuth, async (req, res) => {
  try {
    const { page = 1, limit = 100 } = req.query;
    const offset = (page - 1) * limit;

    const { count, rows } = await ActivityLog.findAndCountAll({
      offset,
      limit: parseInt(limit),
      order: [['createdAt', 'DESC']]
    });

    res.json({ data: rows, total: count, page: parseInt(page), limit: parseInt(limit) });
  } catch (error) {
    res.status(500).json({ error: '获取活动日志失败', message: error.message });
  }
});



// 服务器状态
router.get('/status', adminAuth, (req, res) => {
  try {
    const status = {
      uptime: process.uptime(),
      timestamp: Date.now(),
      memory: process.memoryUsage(),
      cpuUsage: process.cpuUsage(),
      nodeVersion: process.version
    };
    res.json(status);
  } catch (error) {
    res.status(500).json({ error: '获取服务器状态失败', message: error.message });
  }
});

// 获取当前注册口令
router.get('/registration-token', adminAuth, async (req, res) => {
  try {
    const token = await RegistrationToken.findOne({
      where: {
        expiresAt: {
          [Op.gt]: new Date()
        }
      },
      order: [['createdAt', 'DESC']]
    });
    res.json({ token });
  } catch (error) {
    res.status(500).json({ error: '获取注册口令失败', message: error.message });
  }
});

// 生成新的注册口令
router.post('/registration-token', adminAuth, async (req, res) => {
  try {
    // 删除所有过期或有效的令牌
    await RegistrationToken.destroy({
      truncate: true // 使用truncate删除所有记录
    });

    // 生成6位随机数字令牌
    const token = crypto.randomInt(100000, 999999).toString();
    // 设置7天过期时间
    const expiresAt = new Date();
    expiresAt.setDate(expiresAt.getDate() + 7);

    const newToken = await RegistrationToken.create({
      token,
      expiresAt
    });

    res.json({ token: newToken });
  } catch (error) {
    res.status(500).json({ error: '生成注册口令失败', message: error.message });
  }
});

// 验证注册口令
router.post('/registration-token/verify', async (req, res) => {
  try {
    const { token } = req.body;

    const validToken = await RegistrationToken.findOne({
      where: {
        token,
        expiresAt: {
          [Op.gt]: new Date()
        }
      }
    });

    res.json({ isValid: !!validToken });
  } catch (error) {
    res.status(500).json({ error: '验证注册口令失败', message: error.message });
  }
});

module.exports = router;