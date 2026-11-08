const requiredEnvironment = (name) => {
  const value = process.env[name];
  if (!value) {
    throw new Error(`Missing required database environment variable: ${name}`);
  }
  return value;
};

const config = {
  HOST: requiredEnvironment("SOIL_DB_HOST"),
  USER: requiredEnvironment("SOIL_DB_USER"),
  PASSWORD: requiredEnvironment("SOIL_DB_PASSWORD"),
  DB: requiredEnvironment("SOIL_DB_NAME"),
  DIALECT: process.env.SOIL_DB_DIALECT || "mysql"
};

export default config;
