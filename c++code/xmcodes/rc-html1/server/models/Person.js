const { DataTypes } = require('sequelize');
const sequelize = require('../config/db');

const Person = sequelize.define('Person', {
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    autoIncrement: true
  },
  '编号': {
    type: DataTypes.STRING,
    allowNull: false
  },
  '姓名': {
    type: DataTypes.STRING,
    allowNull: false
  },
  '性别': {
    type: DataTypes.STRING,
    allowNull: false
  },
  '出生年月': {
    type: DataTypes.DATE,
    allowNull: false
  },
  '身份证号': {
    type: DataTypes.STRING,
    allowNull: false
  },
  '民族': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '政治面貌': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '学历': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '学位': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '毕业院校': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '专业': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '毕业时间': {
    type: DataTypes.DATE,
    allowNull: true
  },
  '工作单位': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '职务': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '职称': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '联系电话': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '电子邮箱': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '通讯地址': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '邮编': {
    type: DataTypes.STRING,
    allowNull: true
  },
  '入党时间': {
    type: DataTypes.DATE
  },
  '参加工作时间': {
    type: DataTypes.DATE,
    allowNull: true
  },
  '简历': {
    type: DataTypes.TEXT
  },
  '备注': {
    type: DataTypes.TEXT
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
  tableName: 'persons',
  timestamps: true
});

module.exports = Person;