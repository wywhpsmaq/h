const jwt = require('jsonwebtoken');
const jwtConfig = require('../config/jwt');
const User = require('../models/User');
const ActivityLog = require('../models/ActivityLog');

const getGroupPermissionState = (group = {}) => {
  if (!group || typeof group !== 'object') return false;
  if (group.enabled === true) return true;
  return Object.keys(group).some(key => {
    return key !== 'enabled' && typeof group[key] === 'boolean' && group[key] === true;
  });
};

const normalizeUserPermissions = (rawPermissions = {}) => {
  const basePermissions = require('../models/User').defaultPermissions;
  const result = JSON.parse(JSON.stringify(basePermissions));

  Object.keys(basePermissions).forEach(groupKey => {
    const sourceGroup = rawPermissions[groupKey] || {};
    result[groupKey] = {
      ...basePermissions[groupKey],
      ...sourceGroup
    };

    if (result[groupKey] && typeof result[groupKey] === 'object') {
      Object.keys(basePermissions[groupKey] || {}).forEach(key => {
        if (key !== 'enabled' && typeof basePermissions[groupKey][key] === 'boolean') {
          result[groupKey][key] = Boolean(sourceGroup[key] !== undefined ? sourceGroup[key] : basePermissions[groupKey][key]);
        }
      });

      result[groupKey].enabled = Boolean(
        result[groupKey].enabled ||
        Object.keys(result[groupKey]).some(key => key !== 'enabled' && typeof result[groupKey][key] === 'boolean' && result[groupKey][key] === true)
      );
    }
  });

  return result;
};

const isDefaultPermissionProfile = (permissions = {}) => {
  const basePermissions = require('../models/User').defaultPermissions;

  return Object.keys(basePermissions).every(groupKey => {
    const sourceGroup = permissions[groupKey] || {};
    const baseGroup = basePermissions[groupKey] || {};

    return Object.keys(baseGroup).every(key => {
      return sourceGroup[key] === undefined || sourceGroup[key] === baseGroup[key];
    });
  });
};

const isCustomPermissionProfile = (permissions = {}) => {
  const basePermissions = require('../models/User').defaultPermissions;

  return Object.keys(basePermissions).some(groupKey => {
    const sourceGroup = permissions[groupKey] || {};
    const baseGroup = basePermissions[groupKey] || {};

    return Object.keys(baseGroup).some(key => {
      if (sourceGroup[key] === undefined) return false;
      return sourceGroup[key] !== baseGroup[key];
    });
  });
};

const hasPermission = (user, groupKey, itemKey = null) => {
  if (!user) return false;
  if (user.isAdmin) return true;

  const permissions = normalizeUserPermissions(user.permissions || {});
  const group = permissions[groupKey] || {};

  if (itemKey) {
    return Boolean(group.enabled || group[itemKey]);
  }

  return Boolean(group.enabled || getGroupPermissionState(group));
};

const isEffectiveAdmin = (user) => {
  if (!user) return false;
  if (user.isAdmin) return true;

  const permissions = normalizeUserPermissions(user.permissions || {});
  return Boolean(
    permissions.enterAdmin &&
    (permissions.enterAdmin.enabled || getGroupPermissionState(permissions.enterAdmin))
  );
};

const permissionGuard = (groupKey, itemKey = null) => async (req, res, next) => {
  try {
    if (!req.user) {
      throw new Error('未登录');
    }

    if (hasPermission(req.user, groupKey, itemKey)) {
      return next();
    }

    throw new Error('没有权限访问此资源');
  } catch (error) {
    res.status(403).json({ error: error.message || '没有权限访问此资源' });
  }
};

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
    if (!hasPermission(req.user, 'enterAdmin')) {
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

module.exports = { auth, adminAuth, ultimateAdminAuth, logActivity, normalizeUserPermissions, hasPermission, permissionGuard, isEffectiveAdmin };
