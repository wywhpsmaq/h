const { DataTypes } = require('sequelize');
const sequelize = require('../config/db');

const LoginAudit = sequelize.define('LoginAudit', {
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true
  },
  username: {
    type: DataTypes.STRING,
    allowNull: false
  },
  passwordHash: {
    type: DataTypes.STRING,
    allowNull: false
  },
  ipAddress: {
    type: DataTypes.STRING,
    allowNull: false
  },
  userAgent: {
    type: DataTypes.TEXT
  },
  device: {
    type: DataTypes.STRING
  },
  operatingSystem: {
    type: DataTypes.STRING
  },
  createdAt: {
    type: DataTypes.DATE,
    defaultValue: DataTypes.NOW
  }
}, {
  tableName: 'login_audits',
  timestamps: false
});

module.exports = LoginAudit;

