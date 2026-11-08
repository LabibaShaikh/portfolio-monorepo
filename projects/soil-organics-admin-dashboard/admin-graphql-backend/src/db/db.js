import { Sequelize } from 'sequelize';
import config from './config.js'; // Adjust the path as necessary to your configuration file

// Create Sequelize instance
const sequelize = new Sequelize(config.DB, config.USER, config.PASSWORD, {
  host: config.HOST,
  dialect: config.DIALECT,
  logging: console.log, // Enable logging for development
});

export default sequelize;
