const { Sequelize } = require('sequelize');

const connectionString = 'postgresql://neondb_owner:npg_MEUTa30SkWmx@ep-frosty-snow-b7k9697f-pooler.c-13.us-east-1.aws.neon.tech/neondb?sslmode=require&channel_binding=require';

const sequelize = new Sequelize(connectionString, {
  dialect: 'postgres',
  logging: false,
  dialectOptions: {
    ssl: {
      require: true,
      rejectUnauthorized: false
    },
    connectTimeout: 30000,
  },
  pool: {
    max: 10,
    min: 0,
    acquire: 30000,
    idle: 10000
  }
});

module.exports = sequelize;