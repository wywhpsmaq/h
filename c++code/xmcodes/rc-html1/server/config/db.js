const { Sequelize } = require('sequelize');

const sequelize = new Sequelize({
  dialect: 'postgres',
  host: 'localhost',
  port: 5432,
  database: 'rc_html1',
  username: 'postgres',
  password: '159875321', // 默认密码，请根据实际情况修改
  logging: false,
  dialectOptions: {
    connectTimeout: 10000,
  },
  pool: {
    max: 10,
    min: 0,
    acquire: 30000,
    idle: 10000
  }
});

module.exports = sequelize;