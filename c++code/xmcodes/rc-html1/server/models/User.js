const { DataTypes } = require('sequelize');
const bcrypt = require('bcryptjs');
const sequelize = require('../config/db');

const defaultPermissions = {
  dataManagement: {
    enabled: false,
    addData: false,
    editData: false,
    deleteData: false,
    downloadData: false,
    uploadData: false
  },
  changeInfo: {
    enabled: false,
    changePassword: false,
    changeUsername: false
  },
  enterAdmin: {
    enabled: false
  },
  userManagement: {
    enabled: false,
    viewUsers: false,
    manageUsers: false,
    registerUsers: false
  },
  registrationManagement: {
    enabled: false,
    viewTokens: false,
    generateTokens: false,
    viewLoginAudit: false,
    reviewUsers: false
  }
};

const buildAdminPermissions = () => {
  const permissions = JSON.parse(JSON.stringify(defaultPermissions));

  Object.keys(permissions).forEach(groupKey => {
    permissions[groupKey].enabled = true;
    Object.keys(permissions[groupKey]).forEach(key => {
      if (typeof permissions[groupKey][key] === 'boolean') {
        permissions[groupKey][key] = true;
      }
    });
  });

  return permissions;
};

const User = sequelize.define('User', {
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true
  },
  username: {
    type: DataTypes.STRING,
    allowNull: false,
    unique: true
  },
  email: {
    type: DataTypes.STRING,
    allowNull: true,
    unique: true,
    validate: {
      isEmail: value => {
        if (value && !/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value)) {
          throw new Error('邮箱格式不正确');
        }
      }
    }
  },
  password: {
    type: DataTypes.STRING,
    allowNull: false
  },
  isAdmin: {
    type: DataTypes.BOOLEAN,
    defaultValue: false
  },
  isBanned: {
    type: DataTypes.BOOLEAN,
    defaultValue: false
  },
  failedLoginAttempts: {
    type: DataTypes.INTEGER,
    defaultValue: 0
  },
  lockUntil: {
    type: DataTypes.DATE,
    allowNull: true
  },
  lastLogin: {
    type: DataTypes.DATE
  },
  emailVerificationRequired: {
    type: DataTypes.BOOLEAN,
    defaultValue: false
  },
  emailVerified: {
    type: DataTypes.BOOLEAN,
    defaultValue: true
  },
  approvalStatus: {
    type: DataTypes.STRING,
    defaultValue: 'approved'
  },
  permissions: {
    type: DataTypes.JSON,
    defaultValue: defaultPermissions
  },
  createdAt: {
    type: DataTypes.DATE,
    defaultValue: DataTypes.NOW
  },
  updatedAt: {
    type: DataTypes.DATE,
    defaultValue: DataTypes.NOW
  }
}, {
  tableName: 'users',
  hooks: {
    beforeSave: async (user) => {
      if (user.changed('password')) {
        user.password = await bcrypt.hash(user.password, 8);
      }
    }
  }
});

User.prototype.validPassword = async function(password) {
  return await bcrypt.compare(password, this.password);
};

module.exports = User;
module.exports.defaultPermissions = defaultPermissions;
module.exports.buildAdminPermissions = buildAdminPermissions;
