# 重构信息管理系统至rc-html1

## 一、项目概述
将现有基于文件存储的信息管理系统重构为使用PostgreSQL数据库的新系统，保留核心功能并添加主题切换等新特性。

## 二、技术栈
- **前端**：HTML5 + CSS3 + JavaScript (ES6+)
- **后端**：Node.js + Express
- **数据库**：PostgreSQL
- **ORM**：Sequelize (用于简化数据库操作)
- **认证**：JWT Token

## 三、目录结构
```
rc-html1/
├── public/
│   ├── index.html          # 登录页面（保留现有）
│   ├── main.html           # 主页面（重构）
│   ├── main.js             # 主页面逻辑（重构）
│   ├── style1.css          # 登录页样式（保留现有）
│   ├── style2.css          # 主页面样式（重构，支持主题切换）
│   └── sj.txt              # 临时数据文件（迁移后移除）
├── server/
│   ├── app.js              # 主应用入口
│   ├── config/             # 配置文件
│   │   ├── db.js           # 数据库配置
│   │   └── jwt.js          # JWT配置
│   ├── models/             # 数据库模型
│   │   ├── User.js         # 用户模型
│   │   └── Person.js       # 人员数据模型
│   ├── routes/             # API路由
│   │   ├── auth.js         # 认证路由
│   │   ├── data.js         # 数据管理路由
│   │   └── admin.js        # 管理员路由
│   └── middlewares/        # 中间件
│       └── auth.js         # 认证中间件
├── package.json
└── README.md
```

## 四、实现步骤

### 1. 环境搭建与初始化
- 创建新目录 `rc-html1`
- 初始化Node.js项目
- 安装依赖：express, pg, sequelize, jsonwebtoken, bcryptjs, multer
- 配置PostgreSQL数据库连接

### 2. 数据库设计
- 创建 `users` 表：存储用户信息
- 创建 `persons` 表：存储人员数据（对应现有数据）
- 创建 `notices` 表：存储系统公告
- 创建 `activity_logs` 表：存储用户活动日志

### 3. 核心功能实现

#### 3.1 认证系统（保留现有登录页面）
- 保留 `index.html` 和 `style1.css`
- 修改后端认证逻辑，使用数据库存储用户信息
- 实现JWT Token生成与验证

#### 3.2 主页面重构
- 重构 `main.html`：优化布局结构，添加主题切换按钮
- 重构 `style2.css`：支持深色/浅色主题切换
- 重构 `main.js`：使用新的API调用数据库

#### 3.3 数据管理功能
- 实现数据的CRUD操作（连接数据库）
- 实现多条件搜索功能
- 实现数据导入导出功能
- 实现KH功能

#### 3.4 主题切换功能
- 添加主题切换按钮
- 使用CSS变量实现主题切换
- 保存用户主题偏好到本地存储

#### 3.5 左侧导航栏
- 实现数据管理、用户信息、数据分析、系统公告、管理员面板
- 根据用户角色动态显示菜单项

### 4. API设计

#### 认证API
- POST /api/login - 用户登录
- POST /api/logout - 用户退出
- POST /api/change-password - 修改密码

#### 数据管理API
- GET /api/data - 获取数据列表
- POST /api/data - 添加数据
- PUT /api/data/:id - 更新数据
- DELETE /api/data - 删除数据（支持批量）
- POST /api/import-data - 导入数据
- GET /api/export-data - 导出数据
- POST /api/kh - KH功能

#### 系统功能API
- GET /api/notice - 获取系统公告
- POST /api/notice - 更新系统公告（管理员）
- POST /api/load-data - 从服务器加载数据
- POST /api/save-data - 保存数据到服务器

#### 管理员API
- GET /api/admin/users - 获取用户列表
- POST /api/admin/backup - 备份数据
- GET /api/admin/logs - 查看日志

### 5. 数据迁移
- 创建数据迁移脚本，将现有文件数据导入到PostgreSQL数据库
- 支持从现有sj.txt文件导入数据

### 6. 测试与优化
- 测试所有功能是否正常工作
- 优化页面加载速度
- 确保数据库查询效率
- 测试主题切换功能

## 五、预期效果
1. 保留现有登录页面，用户体验保持一致
2. 主页面支持深色/浅色主题切换
3. 所有数据存储在PostgreSQL数据库中，提高数据安全性和查询效率
4. 保留并优化现有功能，包括搜索、添加、删除、导入导出、KH等
5. 左侧导航栏根据用户角色动态显示
6. 提高系统的可扩展性和维护性

## 六、注意事项
1. 确保数据库连接安全，使用环境变量存储敏感信息
2. 实现适当的错误处理和日志记录
3. 确保所有API都有适当的权限验证
4. 测试数据导入导出功能，确保兼容性
5. 确保主题切换功能在所有浏览器中正常工作

## 七、后续优化方向
1. 添加更多数据分析图表
2. 实现用户权限精细化管理
3. 添加数据备份自动定时任务
4. 优化移动端适配
5. 添加数据批量导入导出的进度提示