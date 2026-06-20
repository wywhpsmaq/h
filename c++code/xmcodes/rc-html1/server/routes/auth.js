const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const User = require('../models/User');
const RegistrationToken = require('../models/RegistrationToken');
const { auth } = require('../middlewares/auth');
const jwtConfig = require('../config/jwt');
const { Op } = require('sequelize');

const router = express.Router();

router.post('/login', async (req, res) => {
  try {
    const { username, password } = req.body;
    const user = await User.findOne({ where: { username } });

    if (!user || !(await user.validPassword(password))) {
      return res.status(401).json({ error: '用户名或密码错误' });
    }

    user.lastLogin = new Date();
    await user.save();

    const token = jwt.sign({ id: user.id, username: user.username, isAdmin: user.isAdmin }, jwtConfig.secret, {
      expiresIn: jwtConfig.expiresIn
    });

    res.cookie('token', token, {
      httpOnly: true,
      secure: false,
      maxAge: 24 * 60 * 60 * 1000
    });

    res.json({
      token,
      user: {
        id: user.id,
        username: user.username,
        isAdmin: user.isAdmin
      }
    });
  } catch (error) {
    res.status(500).json({ error: '登录失败', message: error.message });
  }
});

router.post('/logout', (req, res) => {
  try {
    res.clearCookie('token');
    res.json({ message: '退出登录成功' });
  } catch (error) {
    res.status(500).json({ error: '退出登录失败', message: error.message });
  }
});

router.post('/change-password', auth, async (req, res) => {
  try {
    const { oldPassword, newPassword } = req.body;

    if (!oldPassword || !newPassword) {
      return res.status(400).json({ error: '请提供旧密码和新密码' });
    }

    const user = await User.findByPk(req.user.id);

    if (!(await user.validPassword(oldPassword))) {
      return res.status(401).json({ error: '旧密码错误' });
    }

    user.password = newPassword;
    await user.save();

    res.json({ message: '密码修改成功' });
  } catch (error) {
    res.status(500).json({ error: '密码修改失败', message: error.message });
  }
});

router.post('/change-username', auth, async (req, res) => {
  try {
    const { newUsername, password } = req.body;

    if (!newUsername || !password) {
      return res.status(400).json({ error: '请提供新用户名和密码' });
    }

    const user = await User.findByPk(req.user.id);

    if (!(await user.validPassword(password))) {
      return res.status(401).json({ error: '密码错误' });
    }

    // 检查新用户名是否已存在
    const existingUser = await User.findOne({ where: { username: newUsername } });
    if (existingUser && existingUser.id !== req.user.id) {
      return res.status(400).json({ error: '用户名已存在' });
    }

    user.username = newUsername;
    await user.save();

    res.json({ message: '用户名修改成功' });
  } catch (error) {
    res.status(500).json({ error: '用户名修改失败', message: error.message });
  }
});

router.get('/me', auth, async (req, res) => {
  try {
    const user = await User.findByPk(req.user.id, { attributes: ['id', 'username', 'isAdmin', 'lastLogin', 'createdAt'] });
    res.json(user);
  } catch (error) {
    res.status(500).json({ error: '获取用户信息失败', message: error.message });
  }
});

// 用户注册（需要注册口令）
router.post('/register', async (req, res) => {
  try {
    const { username, password, registrationToken } = req.body;

    // 验证参数
    if (!username || !password || !registrationToken) {
      return res.status(400).json({ error: '请提供用户名、密码和注册口令' });
    }

    // 验证注册口令
    const validToken = await RegistrationToken.findOne({
      where: {
        token: registrationToken,
        expiresAt: {
          [Op.gt]: new Date()
        }
      }
    });

    if (!validToken) {
      return res.status(403).json({ error: '注册口令无效或已过期' });
    }

    // 检查用户名是否已存在
    const existingUser = await User.findOne({ where: { username } });
    if (existingUser) {
      return res.status(400).json({ error: '用户名已存在' });
    }

    // 创建用户（默认为普通用户）
    const user = await User.create({
      username,
      password,
      isAdmin: false
    });

    res.status(201).json({ message: '用户注册成功', user: { id: user.id, username: user.username, isAdmin: user.isAdmin } });
  } catch (error) {
    res.status(500).json({ error: '注册失败', message: error.message });
  }
});

module.exports = router;