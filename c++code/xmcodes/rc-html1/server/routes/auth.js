const express = require('express');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const User = require('../models/User');
const RegistrationToken = require('../models/RegistrationToken');
const LoginAudit = require('../models/LoginAudit');
const { auth, hasPermission, isEffectiveAdmin } = require('../middlewares/auth');
const jwtConfig = require('../config/jwt');
const { Op } = require('sequelize');
const router = express.Router();

function getClientInfo(req) {
  const ua = req.headers['user-agent'] || '';
  const isWindows = /Windows/i.test(ua);
  const isMac = /Mac/i.test(ua);
  const isAndroid = /Android/i.test(ua);
  const isIOS = /iPhone|iPad|iPod/i.test(ua);
  const isLinux = /Linux/i.test(ua);

  let os = 'Unknown';
  if (isWindows) os = 'Windows';
  else if (isMac) os = 'MacOS';
  else if (isAndroid) os = 'Android';
  else if (isIOS) os = 'iOS';
  else if (isLinux) os = 'Linux';

  return {
    ipAddress: req.ip || req.headers['x-forwarded-for'] || 'unknown',
    userAgent: ua,
    device: /Mobile|Android|iPhone|iPad/i.test(ua) ? 'Mobile' : 'Desktop',
    operatingSystem: os
  };
}

router.post('/login', async (req, res) => {
  try {
    const { username, password } = req.body;
    const loginKey = (username || '').trim();

    if (!loginKey || !password) {
      return res.status(400).json({ error: '请提供用户名/邮箱和密码' });
    }

    const user = await User.findOne({
      where: {
        [Op.or]: [
          { username: loginKey },
          { email: loginKey }
        ]
      }
    });

    if (!user) {
      return res.status(401).json({ error: '用户名或密码错误' });
    }

    if (user.isBanned) {
      return res.status(403).json({ error: '账户已被封禁' });
    }

    const isAdminAccount = Boolean(user.isAdmin || user.username === 'admin' || isEffectiveAdmin(user));

    if (!isAdminAccount && user.emailVerificationRequired && !user.emailVerified) {
      return res.status(403).json({ error: '该账户邮箱尚未通过审核，暂时无法登录' });
    }

    if (!isAdminAccount && user.approvalStatus && user.approvalStatus !== 'approved') {
      return res.status(403).json({ error: '该账户尚未通过管理员审核，暂时无法登录' });
    }

    const now = new Date();
    if (user.lockUntil && new Date(user.lockUntil) > now) {
      return res.status(423).json({ error: '账户已被锁定，请稍后再试' });
    }

    const isValidPassword = await user.validPassword(password);
    if (!isValidPassword) {
      const attempts = (user.failedLoginAttempts || 0) + 1;
      const lockDuration = attempts >= 5 ? 15 * 60 * 1000 : 5 * 60 * 1000;
      await user.update({
        failedLoginAttempts: attempts,
        lockUntil: attempts >= 5 ? new Date(Date.now() + lockDuration) : null
      });

      await LoginAudit.create({
        username: user.username,
        passwordHash: bcrypt.hashSync(password || '', 8),
        ...getClientInfo(req)
      });

      return res.status(401).json({
        error: attempts >= 5 ? '密码错误次数过多，账户已被临时锁定' : '用户名或密码错误'
      });
    }

    await user.update({
      failedLoginAttempts: 0,
      lockUntil: null,
      lastLogin: now
    });

    await LoginAudit.create({
      username: user.username,
      passwordHash: user.password,
      ...getClientInfo(req)
    });

    const token = jwt.sign({ id: user.id, username: user.username, isAdmin: Boolean(user.isAdmin) }, jwtConfig.secret, {
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
        email: user.email,
        isAdmin: Boolean(user.isAdmin),
        permissions: user.permissions || {}
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
    if (!user) {
      return res.status(404).json({ error: '用户不存在' });
    }

    if (!user.isAdmin && !hasPermission(user, 'changeInfo', 'changePassword')) {
      return res.status(403).json({ error: '没有修改密码权限' });
    }

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
    if (!user) {
      return res.status(404).json({ error: '用户不存在' });
    }

    if (!user.isAdmin && !hasPermission(user, 'changeInfo', 'changeUsername')) {
      return res.status(403).json({ error: '没有修改用户名权限' });
    }

    if (!(await user.validPassword(password))) {
      return res.status(401).json({ error: '密码错误' });
    }

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
    const user = await User.findByPk(req.user.id, { attributes: ['id', 'username', 'email', 'isAdmin', 'lastLogin', 'createdAt', 'permissions'] });
    res.json({
      id: user.id,
      username: user.username,
      email: user.email,
      isAdmin: Boolean(user.isAdmin || isEffectiveAdmin(user)),
      lastLogin: user.lastLogin,
      createdAt: user.createdAt,
      permissions: user.permissions || {}
    });
  } catch (error) {
    res.status(500).json({ error: '获取用户信息失败', message: error.message });
  }
});

router.post('/register', async (req, res) => {
  try {
    const { username, email, password, registrationToken, useEmailVerification } = req.body;

    if (!username || !password) {
      return res.status(400).json({ error: '请提供用户名和密码' });
    }

    const normalizedEmail = email ? String(email).trim() : null;
    const shouldUseEmailVerification = useEmailVerification === true;

    if (normalizedEmail && !/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(normalizedEmail)) {
      return res.status(400).json({ error: '邮箱格式不正确' });
    }

    if (shouldUseEmailVerification) {
      if (!normalizedEmail) {
        return res.status(400).json({ error: '使用邮箱验证时，邮箱不能为空' });
      }
    } else {
      if (!registrationToken) {
        return res.status(400).json({ error: '请提供管理员注册口令或勾选邮箱验证' });
      }

      const validToken = await RegistrationToken.findOne({
        where: {
          token: registrationToken,
          expiresAt: {
            [Op.gt]: new Date()
          }
        }
      });

      if (!validToken) {
        return res.status(403).json({ error: '���册口令无效或已过期' });
      }
    }

    const existingUser = await User.findOne({
      where: {
        [Op.or]: [{ username }, ...(normalizedEmail ? [{ email: normalizedEmail }] : [])]
      }
    });
    if (existingUser) {
      return res.status(400).json({ error: '用户名或邮箱已存在' });
    }

    const user = await User.create({
      username,
      email: normalizedEmail,
      password,
      isAdmin: false,
      emailVerificationRequired: shouldUseEmailVerification,
      emailVerified: !shouldUseEmailVerification,
      approvalStatus: shouldUseEmailVerification ? 'pending' : 'approved'
    });

    res.status(201).json({
      message: shouldUseEmailVerification ? '注册已提交，等待管理员审核通过后方可登录' : '用户注册成功',
      user: { id: user.id, username: user.username, email: user.email, isAdmin: user.isAdmin, approvalStatus: user.approvalStatus }
    });
  } catch (error) {
    res.status(500).json({ error: '注册失败', message: error.message });
  }
});

module.exports = router;