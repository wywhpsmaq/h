# 信息管理系统

一个基于Node.js + Express + PostgreSQL的信息管理系统，支持用户认证、数据管理、主题切换等功能。

## 技术栈

- **后端**: Node.js + Express
- **数据库**: PostgreSQL + Sequelize ORM
- **认证**: JWT (JSON Web Token)
- **前端**: HTML + CSS + JavaScript
- **主题**: 支持深色/浅色模式切换

## 功能特性

### 数据管理
- ✅ 数据列表展示
- ✅ 数据搜索功能
- ✅ 添加数据
- ✅ 编辑数据
- ✅ 删除数据
- ✅ 批量删除
- ✅ 数据导入/导出

### 用户管理
- ✅ 用户登录/退出
- ✅ 密码修改
- ✅ 用户信息展示
- ✅ 管理员权限管理

### 系统功能
- ✅ 主题切换（深色/浅色）
- ✅ 系统公告
- ✅ 数据分析
- ✅ 从服务器加载数据
- ✅ 保存数据到服务器
- ✅ KH功能

### 管理员功能
- ✅ 管理员面板
- ✅ 用户管理
- ✅ 系统维护

## 安装和配置

### 1. 环境要求

- Node.js 14.x 或更高版本
- PostgreSQL 10.x 或更高版本

### 2. 数据库配置

#### 2.1 创建数据库

```sql
CREATE DATABASE rc_html1;
```

#### 2.2 创建用户（可选）

```sql
CREATE USER postgres WITH PASSWORD 'your_password';
GRANT ALL PRIVILEGES ON DATABASE rc_html1 TO postgres;
```

### 3. 应用配置

#### 3.1 修改数据库连接配置

编辑 `server/config/db.js` 文件，修改以下配置：

```javascript
const sequelize = new Sequelize({
  dialect: 'postgres',
  host: 'localhost', // 数据库主机地址
  port: 5432,        // 数据库端口
  database: 'rc_html1', // 数据库名称
  username: 'postgres', // 数据库用户名
  password: 'your_password', // 数据库密码
  // 其他配置...
});
```

#### 3.2 修改JWT配置（可选）

编辑 `server/config/jwt.js` 文件，修改JWT密钥和过期时间：

```javascript
module.exports = {
  secret: 'your_jwt_secret_key', // 替换为自定义密钥
  expiresIn: '24h' // 过期时间
};
```

### 4. 安装依赖

```bash
npm install
```

### 5. 启动应用

```bash
npm start
```

应用将在 `http://localhost:3000` 启动。

## 首次使用

1. 访问 `http://localhost:3000`
2. 使用默认管理员账号登录：
   - 用户名: admin
   - 密码: admin123
3. 登录后可以修改密码

## 项目结构

```
rc-html1/
├── server/                 # 后端代码
│   ├── config/            # 配置文件
│   │   ├── db.js          # 数据库配置
│   │   └── jwt.js         # JWT配置
│   ├── models/            # 数据模型
│   │   ├── User.js        # 用户模型
│   │   ├── Person.js      # 人员数据模型
│   │   ├── Notice.js      # 系统公告模型
│   │   └── ActivityLog.js # 活动日志模型
│   ├── middlewares/       # 中间件
│   │   └── auth.js        # 认证中间件
│   ├── routes/            # 路由
│   │   ├── auth.js        # 认证路由
│   │   ├── data.js        # 数据管理路由
│   │   └── admin.js       # 管理员路由
│   └── app.js             # 应用入口
├── public/                # 前端代码
│   ├── index.html         # 登录页面
│   ├── main.html          # 主页面
│   ├── style1.css         # 登录页面样式
│   ├── style2.css         # 主页面样式
│   └── main.js            # 主页面脚本
├── package.json           # 项目依赖
└── README.md              # 项目说明
```

## 配置说明

### 数据库模型

#### User 模型
| 字段名 | 类型 | 描述 |
|--------|------|------|
| id | INTEGER | 用户ID（主键） |
| username | STRING | 用户名 |
| password | STRING | 密码（加密存储） |
| isAdmin | BOOLEAN | 是否为管理员 |
| lastLogin | DATE | 最后登录时间 |
| createdAt | DATE | 创建时间 |
| updatedAt | DATE | 更新时间 |

#### Person 模型
包含详细的人员信息字段，如姓名、性别、出生年月、身份证号等。

### API 路由

#### 认证路由
- `POST /api/auth/login` - 用户登录
- `POST /api/auth/logout` - 用户退出
- `POST /api/auth/change-password` - 修改密码
- `GET /api/auth/me` - 获取当前用户信息

#### 数据管理路由
- `GET /api/data/persons` - 获取人员数据列表
- `POST /api/data/persons` - 添加人员数据
- `PUT /api/data/persons/:id` - 更新人员数据
- `DELETE /api/data/persons/:id` - 删除人员数据
- `DELETE /api/data/persons` - 批量删除人员数据
- `POST /api/data/import` - 导入数据
- `GET /api/data/export` - 导出数据
- `POST /api/data/kh` - KH功能
- `GET /api/data/load-from-server` - 从服务器加载数据
- `POST /api/data/save-to-server` - 保存数据到服务器

#### 管理员路由
- `GET /api/admin/users` - 获取用户列表
- `POST /api/admin/users` - 创建用户
- `PUT /api/admin/users/:id` - 更新用户信息
- `DELETE /api/admin/users/:id` - 删除用户
- `GET /api/admin/logs` - 获取活动日志
- `GET /api/admin/notices` - 获取系统公告
- `POST /api/admin/notices` - 创建系统公告
- `PUT /api/admin/notices/:id` - 更新系统公告
- `DELETE /api/admin/notices/:id` - 删除系统公告
- `GET /api/admin/status` - 获取服务器状态

## 使用说明

### 登录
1. 访问 `http://localhost:3000`
2. 输入用户名和密码
3. 点击登录按钮

### 数据管理
1. 登录后进入数据管理页面
2. 可以查看、搜索、添加、编辑、删除数据
3. 可以导入/导出数据

### 主题切换
1. 点击右上角的主题切换按钮
2. 切换为深色模式或浅色模式

### 修改密码
1. 点击左侧菜单的"用户信息"
2. 点击"修改密码"按钮
3. 输入旧密码和新密码
4. 点击确定按钮

## 常见问题

### 1. 数据库连接失败

**问题**: 启动应用时出现数据库连接错误

**解决方案**:
- 确保PostgreSQL服务器正在运行
- 确保数据库名称、用户名、密码正确
- 确保数据库用户有足够的权限
- 确保PostgreSQL配置允许密码认证

### 2. 无法登录

**问题**: 输入正确的用户名和密码后无法登录

**解决方案**:
- 确保应用已经启动
- 确保用户名和密码正确
- 检查浏览器控制台是否有错误信息
- 检查服务器日志

### 3. 数据导入失败

**问题**: 导入数据时失败

**解决方案**:
- 确保导入的CSV文件格式正确
- 确保CSV文件包含所有必填字段
- 检查服务器日志

## 开发说明

### 代码规范
- 使用ES6+语法
- 遵循RESTful API设计原则
- 使用模块化设计
- 代码注释清晰

### 安全注意事项
- 敏感数据加密存储
- 使用HTTPS协议（生产环境）
- 定期备份数据库
- 限制登录尝试次数
- 实现CSRF防护

## 许可证

MIT License

## 更新日志

### v1.0.0
- 初始版本发布
- 实现基本的数据管理功能
- 实现用户认证功能
- 实现主题切换功能
- 实现管理员功能

## 贡献

欢迎提交Issue和Pull Request！

## 联系方式

如有问题或建议，请联系开发团队。

---

**说明**: 本系统仅供学习和参考使用，生产环境使用前请进行充分测试和安全评估。