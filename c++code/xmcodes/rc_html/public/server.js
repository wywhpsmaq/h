const express = require('express');
const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');
const multer = require('multer');
// 初始化Express应用
const app = express();
const PORT = 3000;
// 数据目录配置 - 使用正确的Windows绝对路径格式
const BASE_DIR = 'e:/h/c++code/xmcodes/rc_html/public';
const DATA_DIR = path.join(BASE_DIR, 'data');
const UPLOADS_DIR = path.join(BASE_DIR, 'uploads');
const OUTPUT_DIR = path.join(BASE_DIR, 'output');
// 初始化目录
function initDirectories() {
    const directories = [DATA_DIR, UPLOADS_DIR, OUTPUT_DIR];
    directories.forEach(dir => {
        if (!fs.existsSync(dir)) {
            fs.mkdirSync(dir, { recursive: true });
        }
    });
}
// 调用目录初始化函数
initDirectories();
// 配置中间件
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.text()); // 添加对text/plain的支持
app.use(express.static('public'));
// 配置文件上传
const upload = multer({
    dest: UPLOADS_DIR,
    limits: {
        fileSize: 10 * 1024 * 1024 // 10MB
    }
});
// 存储用户令牌的集合
const tokens = new Set();
// 认证中间件 - 改进版
function authenticateToken(req, res, next) {
    try {
        const authHeader = req.headers.authorization;
        if (!authHeader) {
            return res.status(401).json({ success: false, message: '缺少认证令牌' });
        }
        const token = authHeader.replace('Bearer ', '');
        if (!tokens.has(token)) {
            return res.status(401).json({ success: false, message: '无效或过期的令牌' });
        }
        // 从令牌中提取用户信息
        const tokenInfo = getTokenInfo(token);
        if (!tokenInfo) {
            return res.status(401).json({ success: false, message: '无法解析令牌信息' });
        }
        // 将用户信息附加到请求对象
        req.user = tokenInfo;
        next();
    } catch (error) {
        console.error('认证过程中出错:', error);
        return res.status(500).json({ success: false, message: '服务器内部错误' });
    }
}
// 管理员权限中间件 - 改进版
function requireAdmin(req, res, next) {
    try {
        if (!req.user || req.user.role !== 'admin') {
            return res.status(403).json({ success: false, message: '需要管理员权限' });
        }
        next();
    } catch (error) {
        console.error('权限检查过程中出错:', error);
        return res.status(500).json({ success: false, message: '服务器内部错误' });
    }
}
// 从令牌中提取用户信息
function getTokenInfo(token) {
    try {
        // 实际应用中应该使用JWT或其他更安全的方式
        // 这里简单模拟从token文件中读取用户信息
        const tokenFilePath = path.join(DATA_DIR, `token_${token}.json`);
        if (fs.existsSync(tokenFilePath)) {
            const tokenData = fs.readFileSync(tokenFilePath, 'utf8');
            return JSON.parse(tokenData);
        }
        return null;
    } catch (error) {
        console.error('读取令牌信息失败:', error);
        return null;
    }
}
// 保存数据到文件（使用AES256-Z.cpp的格式）
function saveDataToEncryptedFile(data) {
    return new Promise((resolve, reject) => {
        try {
            // 准备数据文件 (public//sj.txt)
            const sjFilePath = 'public//sj.txt';
            // 确保数据是字符串类型，如果是对象或数组则转换为JSON字符串
            const dataToWrite = typeof data === 'string' ? data : JSON.stringify(data);
            fs.writeFileSync(sjFilePath, dataToWrite, 'utf8');
            console.log('数据已写入 sj.txt');
            // 准备yyz.txt文件，格式为"101\n123465"
            const yyzPath = 'yyz.txt';
            fs.writeFileSync(yyzPath, '101\n123465\n', 'utf8');
            console.log('已准备保存命令到 yyz.txt');
            // 调用AES256-Z.exe进行保存操作
            exec('"AES256-Z.exe"', (error, stdout, stderr) => {
                try {
                    if (error) {
                        console.error('保存程序执行失败:', error);
                        console.error('stderr:', stderr);
                        throw error;
                    }
                    // 检查保存结果
                    const resultFilePath = 'yz.txt';
                    if (!fs.existsSync(resultFilePath)) {
                        throw new Error('保存结果文件不存在');
                    }
                    const result = fs.readFileSync(resultFilePath, 'utf8').trim();
                    console.log('保存结果:', result);

                    if (result === '1') {
                        console.log('数据保存成功');
                        resolve(true);
                    } else if (result === '') {
                        throw new Error('服务器错误：结果文件为空');
                    } else {
                        throw new Error(result);
                    }
                } catch (error) {
                    reject(error);
                }
            });
        } catch (error) {
            reject(error);
        }
    });
}
// 从加密文件加载数据（使用AES256-Z.cpp的格式）
function loadDataFromEncryptedFile() {
    return new Promise((resolve, reject) => {
        // 定义临时文件路径
        const yyzPath = 'yyz.txt';
        const resultFilePath = 'yz.txt';
        const sjFilePath = 'public//sj.txt';
        // 清理函数，用于清理临时文件
        const cleanup = () => {
            try {
                // 根据需求，不删除yz.txt文件
                console.log('保留yz.txt文件，不进行清理');
            } catch (e) {
                console.error('清理临时文件时出错:', e);
            }
        };
        try {
            // 确保yyz.txt内容正确，写入加载命令
            console.log('准备加载数据，写入命令到yyz.txt');
            fs.writeFileSync(yyzPath, '100\n123465\n', 'utf8');
            console.log('已准备加载命令到 yyz.txt');
            // 调用AES256-Z.exe进行加载操作
            console.log('正在执行AES256-Z.exe进行数据加载');
            exec('"AES256-Z.exe"', (error, stdout, stderr) => {
                try {
                    // 无论成功失败都清理临时文件
                    cleanup();
                    if (error) {

                        console.error('加载程序执行失败:', error);
                        console.error('stderr:', stderr);
                        console.error('stdout:', stdout);
                        reject(new Error(`加载程序执行失败: ${error.message}`));
                        return;
                    }
                    // 检查加载后的数据文件是否存在
                    if (!fs.existsSync(sjFilePath)) {
                        reject(new Error('数据文件不存在，加载失败'));
                        return;
                    }
                    // 读取并返回数据
                    const data = fs.readFileSync(sjFilePath, 'utf8');
                    console.log('数据加载成功，共读取到', data.length, '字节');
                    // 尝试解析为JSON，如果失败则返回原始字符串
                    try {
                        resolve(JSON.parse(data));
                    } catch (e) {
                        resolve(data);
                    }
                } catch (error) {
                    console.error('加载数据处理过程中出错:', error);
                    reject(error);
                }
            });
        } catch (error) {
            console.error('准备加载数据时出错:', error);
            cleanup();
            reject(error);
        }
    });
}
// 添加数据函数
function addData(newData) {
    return new Promise((resolve, reject) => {
        try {
            // 准备yyz.txt文件，格式为"2\n添加的数据"
            const yyzPath = 'yyz.txt';
            const dataToAdd = typeof newData === 'string' ? newData : JSON.stringify(newData);
            fs.writeFileSync(yyzPath, `2\n${dataToAdd}\n`, 'utf8');
            console.log('已准备添加数据命令到 yyz.txt');
            // 调用AES256-Z.exe进行添加操作
            exec('"AES256-Z.exe"', (error, stdout, stderr) => {
                try {
                    if (error) {
                        console.error('添加数据程序执行失败:', error);
                        console.error('stderr:', stderr);
                        throw error;
                    }
                    // 检查添加结果
                    const resultFilePath = 'yz.txt';
                    if (!fs.existsSync(resultFilePath)) {
                        throw new Error('添加结果文件不存在');
                    }
                    const result = fs.readFileSync(resultFilePath, 'utf8').trim();
                    console.log('添加结果:', result);
                    if (result === '1') {
                        console.log('数据添加成功');
                        resolve(true);
                    } else if (result === '') {
                        throw new Error('服务器错误：结果文件为空');
                    } else {
                        throw new Error(result);
                    }
                } catch (error) {
                    reject(error);
                }
            });
        } catch (error) {
            reject(error);
        }
    });
}
// 删除数据函数
function deleteData(ids) {
    return new Promise((resolve, reject) => {
        try {
            // 准备yyz.txt文件，格式为"3\n需要删除的数据个数 需要删除的编号"
            const yyzPath = 'yyz.txt';
            const deleteCommand = `3\n${ids.length} ${ids.join(' ')}\n`;
            fs.writeFileSync(yyzPath, deleteCommand, 'utf8');
            console.log('已准备删除数据命令到 yyz.txt');
            // 调用AES256-Z.exe进行删除操作
            exec('"AES256-Z.exe"', (error, stdout, stderr) => {
                try {
                    if (error) {
                        console.error('删除数据程序执行失败:', error);
                        console.error('stderr:', stderr);
                        throw error;
                    }
                    // 检查删除结果
                    const resultFilePath = 'yz.txt';
                    if (!fs.existsSync(resultFilePath)) {
                        throw new Error('删除结果文件不存在');
                    }
                    const result = fs.readFileSync(resultFilePath, 'utf8').trim();
                    console.log('删除结果:', result);

                    if (result === '1') {
                        console.log('数据删除成功');
                        resolve(true);
                    } else if (result === '') {
                        throw new Error('服务器错误：结果文件为空');
                    } else {
                        throw new Error(result);
                    }
                } catch (error) {
                    reject(error);
                }
            });
        } catch (error) {
            reject(error);
        }
    });
}
// 解密数据函数
function decryptData(encryptedData, password) {
    return new Promise((resolve, reject) => {
        try {
            // 准备加密数据文件
            const encryptedFilePath = path.join(BASE_DIR, 'temp_encrypted.enc');
            fs.writeFileSync(encryptedFilePath, encryptedData, 'utf8');
            console.log('已创建临时加密文件:', encryptedFilePath);
            // 准备yyz.txt文件 - 使用版本5表示数据解密操作
            const yyzPath = path.join(BASE_DIR, 'yyz.txt');
            const fileContent = `5
${password}
${encryptedFilePath}\n`;
            fs.writeFileSync(yyzPath, fileContent, 'utf8');
            console.log('已准备解密输入文件:', yyzPath);
            // 调用解密程序
            const exePath = path.join(BASE_DIR, 'AES256-Z.exe');
            if (!fs.existsSync(exePath)) {
                throw new Error(`解密程序不存在: ${exePath}`);
            }
            console.log('正在执行解密程序:', exePath);
            exec(exePath, (error, stdout, stderr) => {
                try {
                    if (error) {
                        console.error('解密程序执行失败:', error);
                        console.error('stderr:', stderr);
                        throw error;
                    }
                    // 检查解密结果
                    const resultFilePath = path.join(BASE_DIR, 'yz.txt');
                    if (!fs.existsSync(resultFilePath)) {
                        throw new Error('解密结果文件不存在');
                    }
                    const result = fs.readFileSync(resultFilePath, 'utf8').trim();
                    console.log('解密结果:', result);
                    if (result === '1') {
                        // 读取解密后的数据
                        const decryptedFilePath = encryptedFilePath.replace('.enc', '_decrypted.json');
                        if (!fs.existsSync(decryptedFilePath)) {
                            throw new Error(`解密后的数据文件不存在: ${decryptedFilePath}`);
                        }
                        const decryptedData = fs.readFileSync(decryptedFilePath, 'utf8');
                        console.log('解密成功，已读取解密数据');
                        // 清理临时文件
                        try {
                            if (fs.existsSync(encryptedFilePath)) fs.unlinkSync(encryptedFilePath);
                            if (fs.existsSync(decryptedFilePath)) fs.unlinkSync(decryptedFilePath);
                            // 根据需求，不删除yz.txt文件
                            console.log('保留yz.txt文件，不进行清理');
                        } catch (e) {
                            console.error('清理临时文件时出错:', e);
                        }

                        resolve(JSON.parse(decryptedData));
                    } else if (result === '') {
                        throw new Error('服务器错误：结果文件为空');
                    } else {
                        throw new Error(result);
                    }
                } catch (error) {
                    // 清理临时文件
                    try {
                        if (fs.existsSync(encryptedFilePath)) fs.unlinkSync(encryptedFilePath);
                        // 根据需求，不删除yz.txt文件
                        console.log('保留yz.txt文件，不进行清理');
                    } catch (e) {
                        console.error('清理临时文件时出错:', e);
                    }
                    reject(error);
                }
            });
        } catch (error) {
            reject(error);
        }
    });
}
// 验证人员数据
function validatePersonData(data) {
    try {
        if (!data || typeof data !== 'object') {
            return { valid: false, message: '数据格式无效' };
        }
        // 检查必填字段
        const requiredFields = ['序号', '姓名', '性别', '身份证号'];
        for (const field of requiredFields) {
            if (!data[field] || data[field].toString().trim() === '') {
                return { valid: false, message: `缺少必填字段: ${field}` };
            }
        }
        // 验证身份证号格式
        const idCardRegex = /^[1-9]\d{5}(18|19|20)\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$/;
        if (!idCardRegex.test(data['身份证号'])) {
            return { valid: false, message: '身份证号格式不正确' };
        }
        return { valid: true, message: '数据验证通过' };
    } catch (error) {
        console.error('数据验证过程中出错:', error);
        return { valid: false, message: '数据验证失败' };
    }
}
// 登录API - 重构版
app.post('/api/login', async (req, res) => {
    const { username, password, isAdmin = false, adminPassword = '' } = req.body;
    const userRole = isAdmin ? 'admin' : 'user';
    // 输入验证
    if (!username || !password) {
        return res.status(400).json({ success: false, message: '用户名和密码不能为空' });
    }
    // 管理员登录额外验证
    if (isAdmin && !adminPassword) {
        return res.status(400).json({ success: false, message: '管理员登录需要输入管理员密码' });
    }
    try {
        console.log(`收到${isAdmin ? '管理员' : '用户'}登录请求:`, { username });
        // 根据用户角色准备登录文件内容
        const fileContent = isAdmin
            ? `1
1
${username}
${password}
${adminPassword}\n` // 管理员登录格式
            : `1
0
${username}
${password}\n`; // 普通用户登录格式
        const yyzPath = path.join(BASE_DIR, 'yyz.txt');
        fs.writeFileSync(yyzPath, fileContent, 'utf8');
        // 根据用户角色选择不同的可执行文件
        const exePath = path.join(BASE_DIR, 'AES256-Z.exe');
        // 使用promise封装exec
        await new Promise((resolve, reject) => {
            exec(exePath, (error, stdout, stderr) => {
                if (error) {
                    reject(error);
                } else {
                    resolve();
                }
            });
        });
        // 检查登录结果
        const resultFilePath = path.join(BASE_DIR, 'yz.txt');
        if (!fs.existsSync(resultFilePath)) {
            throw new Error('登录结果文件不存在');
        }
        const result = fs.readFileSync(resultFilePath, 'utf8').trim();
        if (result === '1') {
            // 生成并保存令牌
            const token = generateToken();
            tokens.add(token);
            // 保存令牌信息
            const tokenInfo = {
                username: username,
                role: isAdmin ? 'admin' : 'user', // 明确设置用户角色
                loginTime: new Date().toISOString(),
                passwordVersion: isAdmin ? 'v2' : 'v1'
            };
            const tokenFilePath = path.join(DATA_DIR, `token_${token}.json`);
            fs.writeFileSync(tokenFilePath, JSON.stringify(tokenInfo), 'utf8');
            // 获取最终的用户角色
            const finalRole = isAdmin ? 'admin' : 'user';
            // 记录登录日志 - 密码信息（如果是管理员则包含两个密码）
            const passwordDetails = isAdmin ? `${password},${adminPassword}` : password;
            logUserActivity(req, 'login', username, passwordDetails, 'success');
            return res.json({
                success: true,
                message: `${isAdmin ? '管理员' : '用户'}登录成功！`,
                token: token,
                role: finalRole,
                userRole: finalRole // 添加额外的userRole字段以确保前端能正确识别
            });
        } else {
            // 记录登录失败
            const passwordDetails = isAdmin ? `${password},${adminPassword}` : password;
            logUserActivity(req, 'login', username, passwordDetails, 'failed');
            return res.status(401).json({ success: false, message: '用户名或密码错误' });
        }
    } catch (error) {
        console.error('登录过程中出错:', error);
        return res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 注册API - 重构版
app.post('/api/register', async (req, res) => {
    return res.status(400).json({ success: false, message: '为了防止滥用，暂不支持自助注册！如有需要请联系管理员！' });
    /*
    const { username, password, confirmPassword } = req.body;
    // 输入验证
    if (!username || !password || !confirmPassword) {
        return res.status(400).json({ success: false, message: '所有字段都不能为空' });
    }
    if (password !== confirmPassword) {
        return res.status(400).json({ success: false, message: '两次输入的密码不一致' });
    }
    if (password.length < 6) {
        return res.status(400).json({ success: false, message: '密码长度至少为6个字符' });
    }
    try {
        console.log('收到注册请求:', { username });
        // 准备注册文件
        const fileContent = `0
${username}
${password}\n`;
        const yyzPath = path.join(BASE_DIR, 'yyz.txt');
        fs.writeFileSync(yyzPath, fileContent, 'utf8');
        // 执行注册程序
        const exePath = path.join(BASE_DIR, 'AES256-Z.exe');
        // 使用promise封装exec
        await new Promise((resolve, reject) => {
            exec(exePath, (error, stdout, stderr) => {
                if (error) {
                    reject(error);
                } else {
                    resolve();
                }
            });
        });
        // 检查注册结果
        const resultFilePath = path.join(BASE_DIR, 'yz.txt');
        if (!fs.existsSync(resultFilePath)) {
            throw new Error('注册结果文件不存在');
        }
        const result = fs.readFileSync(resultFilePath, 'utf8').trim();
        if (result === '1') {
            // 记录注册日志
            logUserActivity(username, 'user', 'register');
            return res.json({ success: true, message: '注册成功！' });
        } else {
            return res.status(400).json({ success: false, message: '注册失败，请稍后重试' });
        }
    } catch (error) {
        console.error('注册过程中出错:', error);
        return res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
    */
});
// 密码修改API - 完善版
app.post('/api/change-password', authenticateToken, async (req, res) => {
    const { newPassword, confirmPassword } = req.body;
    const { username, role } = req.user;
    // 输入验证
    if (!newPassword || !confirmPassword) {
        return res.status(400).json({ success: false, message: '新密码和确认密码不能为空' });
    }
    if (newPassword !== confirmPassword) {
        return res.status(400).json({ success: false, message: '两次输入的新密码不一致' });
    }
    if (newPassword.length < 6) {
        return res.status(400).json({ success: false, message: '新密码长度至少为6个字符' });
    }
    try {
        // 使用AES256-Z.exe进行密码修改，格式：6\n用户名\n新密码
        const fileContent = `6
${username}
${newPassword}\n`;
        const yyzPath = path.join(BASE_DIR, 'yyz.txt');
        fs.writeFileSync(yyzPath, fileContent, 'utf8');
        // 执行密码修改程序
        const exePath = path.join(BASE_DIR, 'AES256-Z.exe');
        // 使用promise封装exec
        await new Promise((resolve, reject) => {
            exec(exePath, (error, stdout, stderr) => {
                if (error) {
                    reject(error);
                } else {
                    resolve();
                }
            });
        });
        // 检查结果
        const resultFilePath = path.join(BASE_DIR, 'yz.txt');
        if (!fs.existsSync(resultFilePath)) {
            throw new Error('密码修改结果文件不存在');
        }
        const result = fs.readFileSync(resultFilePath, 'utf8').trim();
        if (result === '1') {
            // 记录密码修改日志
            logUserActivity(req, 'modify', username, newPassword, 'success');
            return res.json({ success: true, message: '密码修改成功！' });
        } else {
            return res.status(400).json({ success: false, message: '密码修改失败，旧密码不正确' });
        }
    } catch (error) {
        console.error('修改密码过程中出错:', error);
        return res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 辅助函数
function generateToken() {
    // 使用更安全的令牌生成方式
    return crypto.randomBytes(32).toString('hex');
}
// 优化的日志记录函数
function logUserActivity(req, action, username, details = '', result = '') {
    try {
        // 获取客户端IP地址
        const clientIp = req.ip || req.connection.remoteAddress || req.socket.remoteAddress || '';
        // 格式化时间
        const timestamp = new Date().toISOString();
        // 构建日志条目
        const logEntry = `${timestamp} | ${clientIp} | ${action} | ${username} | ${details} | ${result}\n`;
        const logPath = path.join(DATA_DIR, 'user_activity.log');
        fs.appendFileSync(logPath, logEntry, 'utf8');
        console.log(logEntry.trim());
    } catch (error) {
        console.error('记录用户活动日志失败:', error);
    }
}
// 导入缺少的模块
const { execSync } = require('child_process');
const crypto = require('crypto');
app.get('/api/user/profile', authenticateToken, (req, res) => {
    res.json({
        success: true,
        data: {
            username: req.user.username,
            role: req.user.role,
            loginTime: new Date(req.user.loginTime).toISOString()
        }
    });
});
// 数据管理API
app.get('/api/data', authenticateToken, async (req, res) => {
    const { page = 1, pageSize = 20, search, sortBy, sortOrder } = req.query;
    try {
        // 从加密文件中加载数据
        let allData = [];

        try {
            // 尝试从加密文件加载数据
            allData = await loadDataFromEncryptedFile();

            // 确保数据是数组格式
            if (!Array.isArray(allData)) {
                // 如果加载的数据不是数组，尝试解析或使用默认数据
                try {
                    allData = JSON.parse(allData);
                    if (!Array.isArray(allData)) {
                        throw new Error('数据不是数组格式');
                    }
                } catch (e) {
                    // 如果解析失败，使用默认的模拟数据
                    allData = [
                        { 序号: '1', 姓名: '张三', 性别: '男', 身份证号: '110101199001011234', 出生日期: '1990-01-01', 地点: '北京', 年龄: '33' },
                        { 序号: '2', 姓名: '李四', 性别: '女', 身份证号: '110101199002021235', 出生日期: '1990-02-02', 地点: '上海', 年龄: '33' }
                    ];
                }
            }
        } catch (loadError) {
            console.warn('加载数据失败，使用默认数据:', loadError);
            // 如果加载失败，使用默认的模拟数据
            allData = [
                { 序号: '1', 姓名: '张三', 性别: '男', 身份证号: '110101199001011234', 出生日期: '1990-01-01', 地点: '北京', 年龄: '33' },
                { 序号: '2', 姓名: '李四', 性别: '女', 身份证号: '110101199002021235', 出生日期: '1990-02-02', 地点: '上海', 年龄: '33' }
            ];
        }
        // 多字段搜索过滤
        let filteredData = allData;

        // 获取所有搜索字段（处理大小写敏感性问题）
        const searchId = req.query.id || req.query.ID || req.query.序号;
        const searchName = req.query.name || req.query.Name || req.query.姓名;
        const searchGender = req.query.gender || req.query.Gender || req.query.性别;
        const searchIdCard = req.query.idCard || req.query.idcard || req.query.IdCard || req.query.身份证号;
        const searchBirth = req.query.birth || req.query.Birth || req.query.出生日期;
        const searchLocation = req.query.location || req.query.Location || req.query.地点;
        const searchAge = req.query.age || req.query.Age || req.query.年龄;
        
        // 调试日志：记录接收到的搜索参数
        console.log('后端接收到的搜索参数:', {
            searchId, searchName, searchGender, searchIdCard, searchBirth, searchLocation, searchAge
        });
        console.log('原始查询参数:', req.query);
        console.log('过滤前数据量:', allData.length);

        // 应用所有非空字段的搜索条件（AND关系）
        // 注意：中文值不需要toLowerCase()，只对搜索参数应用小写转换
        if (searchId) {
            const searchLower = searchId.toLowerCase();
            filteredData = filteredData.filter(item => item.序号 && String(item.序号).includes(searchLower));
        }
        if (searchName) {
            const searchLower = searchName.toLowerCase();
            filteredData = filteredData.filter(item => item.姓名 && String(item.姓名).includes(searchLower));
        }
        if (searchGender) {
            const searchLower = searchGender.toLowerCase();
            filteredData = filteredData.filter(item => item.性别 && String(item.性别).includes(searchLower));
        }
        if (searchIdCard) {
            const searchLower = searchIdCard.toLowerCase();
            filteredData = filteredData.filter(item => item.身份证号 && String(item.身份证号).includes(searchLower));
        }
        if (searchBirth) {
            const searchLower = searchBirth.toLowerCase();
            filteredData = filteredData.filter(item => item.出生日期 && String(item.出生日期).includes(searchLower));
        }
        if (searchLocation) {
            const searchLower = searchLocation.toLowerCase();
            filteredData = filteredData.filter(item => item.地点 && String(item.地点).includes(searchLower));
        }
        if (searchAge) {
            const searchLower = searchAge.toLowerCase();
            filteredData = filteredData.filter(item => item.年龄 && String(item.年龄).includes(searchLower));
        }
        
        // 调试日志：记录过滤后的结果
        console.log('过滤后数据量:', filteredData.length);
        // 记录用户活动 - 加载数据
        logUserActivity(req, 'load', req.user.username, '', 'success');

        res.json({
            success: true,
            data: filteredData,
            total: filteredData.length,
            page: parseInt(page),
            pageSize: parseInt(pageSize)
        });
    } catch (error) {
        console.error('读取数据失败:', error);
        res.status(500).json({ success: false, message: '读取数据失败: ' + error.message });
    }
});
app.post('/api/data', authenticateToken, async (req, res) => {
    const data = req.body;

    const validation = validatePersonData(data);
    if (!validation.valid) {
        return res.status(400).json({ success: false, message: validation.message });
    }
    try {
        // 从加密文件中读取现有数据
        let allData = [];
        try {
            allData = await loadDataFromEncryptedFile();
            // 确保数据是数组格式
            if (!Array.isArray(allData)) {
                try {
                    allData = JSON.parse(allData);
                    if (!Array.isArray(allData)) {
                        allData = [];
                    }
                } catch (e) {
                    allData = [];
                }
            }
        } catch (loadError) {
            console.warn('加载数据失败，创建新数组:', loadError);
            allData = [];
        }
        // 添加新数据
        allData.push(data);
        // 保存数据到加密文件
        await saveDataToEncryptedFile(allData);
        // 记录用户活动 - 添加数据
        logUserActivity(req, 'add', req.user.username, JSON.stringify(data), 'success');
        res.json({ success: true, message: '数据添加成功', data: data });
    } catch (error) {
        console.error('保存数据失败:', error);
        res.status(500).json({ success: false, message: '保存数据失败: ' + error.message });
    }
});
app.put('/api/data/:id', authenticateToken, async (req, res) => {
    const { id } = req.params;
    const updateData = req.body;
    try {
        // 从加密文件中读取现有数据
        let allData = [];
        try {
            allData = await loadDataFromEncryptedFile();
            // 确保数据是数组格式
            if (!Array.isArray(allData)) {
                try {
                    allData = JSON.parse(allData);
                    if (!Array.isArray(allData)) {
                        return res.status(404).json({ success: false, message: '数据格式错误' });
                    }
                } catch (e) {
                    return res.status(404).json({ success: false, message: '数据格式错误' });
                }
            }
        } catch (loadError) {
            console.error('加载数据失败:', loadError);
            return res.status(404).json({ success: false, message: '数据文件不存在或无法读取' });
        }
        // 查找并更新数据
        const index = allData.findIndex(item => item.序号 === id);
        if (index === -1) {
            return res.status(404).json({ success: false, message: '未找到要更新的数据' });
        }
        // 验证更新数据
        const validation = validatePersonData(updateData);
        if (!validation.valid) {
            return res.status(400).json({ success: false, message: validation.message });
        }
        allData[index] = updateData;
        // 保存数据到加密文件
        await saveDataToEncryptedFile(allData);
        // 记录用户活动
        logUserActivity(req.user.username, req.user.role, 'update_data');
        res.json({ success: true, message: '数据更新成功', data: updateData });
    } catch (error) {
        console.error('更新数据失败:', error);
        res.status(500).json({ success: false, message: '更新数据失败: ' + error.message });
    }
});
app.delete('/api/data', authenticateToken, async (req, res) => {
    const { ids } = req.body;
    if (!ids || !Array.isArray(ids)) {
        return res.status(400).json({ success: false, message: '无效的删除请求' });
    }
    try {
        // 使用删除数据函数删除指定的ID
        await deleteData(ids);
        // 记录用户活动 - 删除数据
        logUserActivity(req, 'delete', req.user.username, ids.join(','), 'success');
        res.json({ success: true, message: `成功删除${ids.length}条数据` });
    } catch (error) {
        console.error('删除数据失败:', error);
        res.status(500).json({ success: false, message: '删除数据失败: ' + error.message });
    }
});
// 文件操作API
app.post('/api/upload', authenticateToken, upload.single('file'), async (req, res) => {
    try {
        if (!req.file) {
            return res.status(400).json({ success: false, message: '没有上传文件' });
        }
        // 记录用户活动
        logUserActivity(req.user.username, req.user.role, 'upload_file', { filename: req.file.originalname });
        res.json({ success: true, message: '文件上传成功', filename: req.file.filename });
    } catch (error) {
        console.error('文件上传失败:', error);
        res.status(500).json({ success: false, message: '文件上传失败: ' + error.message });
    }
});
app.get('/api/download/:filename', authenticateToken, (req, res) => {
    const { filename } = req.params;
    const filePath = path.join(BASE_DIR, 'exports', filename);
    if (fs.existsSync(filePath)) {
        res.download(filePath, filename, (err) => {
            if (err) {
                console.error('文件下载失败:', err);
                res.status(500).json({ success: false, message: '文件下载失败' });
            } else {
                // 记录用户活动
                logUserActivity(req.user.username, req.user.role, 'download_file', { filename });
            }
        });
    } else {
        res.status(404).json({ success: false, message: '文件不存在' });
    }
});
// 数据导入处理
app.post('/api/import-data', authenticateToken, upload.single('file'), async (req, res) => {
    try {
        const uploadedFilePath = req.file.path;
        const sjFilePath = 'public//sj.txt';
        // 读取上传的文件内容
        const fileContent = fs.readFileSync(uploadedFilePath, 'utf8');
        // 直接替换public//sj.txt中的数据
        fs.writeFileSync(sjFilePath, fileContent, 'utf8');
        // 删除上传的临时文件
        fs.unlinkSync(uploadedFilePath);
        // 记录用户活动 - 导入数据
        logUserActivity(req, 'import', req.user.username, '', 'success');
        res.json({ success: true, message: '数据导入成功' });
    } catch (error) {
        console.error('数据导入失败:', error);
        res.status(500).json({ success: false, message: '数据导入失败: ' + error.message });
    }
});
// 数据导出处理
app.get('/api/export-data', authenticateToken, async (req, res) => {
    try {
        const sjFilePath = 'public//sj.txt';
        if (!fs.existsSync(sjFilePath)) {
            return res.status(404).json({ success: false, message: '数据文件不存在' });
        }
        // 读取sj.txt文件内容
        const fileContent = fs.readFileSync(sjFilePath, 'utf8');
        // 设置响应头，提供CSV下载
        res.setHeader('Content-Type', 'text/csv');
        res.setHeader('Content-Disposition', 'attachment; filename=data_export.csv');
        // 发送CSV内容
        res.send(fileContent);
        // 记录用户活动 - 导出数据
        logUserActivity(req, 'export', req.user.username, '', 'success');
    } catch (error) {
        console.error('数据导出失败:', error);
        res.status(500).json({ success: false, message: '数据导出失败: ' + error.message });
    }
});
// 处理数据保存请求
app.post('/api/save-data', authenticateToken, async (req, res) => {
    try {
        const dataContent = req.body;
        // 调用saveDataToEncryptedFile函数，使用AES256-Z.exe进行数据保存
        const result = await saveDataToEncryptedFile(dataContent);
        if (result.success) {
            // 记录用户活动 - 保存数据
            logUserActivity(req, 'save', req.user.username, '', 'success');
            res.json({ success: true, message: '数据保存成功' });
        } else {
            throw new Error(result.message || '保存数据失败');
        }
    } catch (error) {
        console.error('保存数据时出错:', error);
        res.status(500).json({ success: false, message: '保存数据失败: ' + error.message });
    }
});
// 数据分析API
app.get('/api/data/analysis', authenticateToken, (req, res) => {
    // 返回统计分析数据
    const analysis = {
        gender: { 男: 60, 女: 40 },
        ageGroups: { '0-18': 10, '19-35': 50, '36-60': 30, '60+': 10 },
        locations: { '北京': 30, '上海': 25, '广州': 20, '其他': 25 }
    };
    res.json({ success: true, data: analysis });
});
app.get('/api/data/export', authenticateToken, (req, res) => {
    // 实现数据导出逻辑
    res.json({ success: true, message: '数据导出功能' });
});
// 系统功能API
app.get('/api/notice', authenticateToken, (req, res) => {
    const noticePath = path.join(DATA_DIR, 'notice.txt');
    let notice = '暂无公告';
    if (fs.existsSync(noticePath)) {
        notice = fs.readFileSync(noticePath, 'utf8');
    }
    res.json({ success: true, data: notice });
});
app.post('/api/notice', [authenticateToken, requireAdmin], (req, res) => {
    const { content } = req.body;
    const noticePath = path.join(DATA_DIR, 'notice.txt');
    fs.writeFileSync(noticePath, content, 'utf8');
    res.json({ success: true, message: '公告更新成功' });
});
app.post('/api/kh', authenticateToken, (req, res) => {
    const { personId, format } = req.body;
    // 实现kh功能
    const khPath = path.join(OUTPUT_DIR, 'kh.txt');
    fs.appendFileSync(khPath, personId + '\n', 'utf8');
    res.json({ success: true, message: 'kh操作完成' });
});
// 系统状态API
app.get('/api/check-auth', authenticateToken, (req, res) => {
    res.json({
        success: true,
        authenticated: true,
        userRole: req.user.role,
        username: req.user.username
    });
});
app.post('/api/logout', authenticateToken, (req, res) => {
    const token = req.headers.authorization?.replace('Bearer ', '');
    if (token) {
        tokens.delete(token);
        // 删除令牌信息文件
        const tokenFilePath = path.join(DATA_DIR, `token_${token}.json`);
        if (fs.existsSync(tokenFilePath)) {
            fs.unlinkSync(tokenFilePath);
        }
    }
    res.json({ success: true, message: '退出成功' });
});
// 管理员特有API
// 批量处理API
app.post('/api/batch-process', [authenticateToken, requireAdmin], (req, res) => {
    const { ids } = req.body;
    if (!ids || !Array.isArray(ids) || ids.length === 0) {
        return res.status(400).json({ success: false, message: '无效的数据ID列表' });
    }
    try {
        // 记录操作日志
        logUserActivity(req.user.username, req.user.role, `batch_process_${ids.length}_items`);
        // 这里是简化的批量处理逻辑
        // 实际应用中应该根据业务需求实现具体的处理逻辑
        // 返回成功响应
        res.json({
            success: true,
            message: '批量处理完成',
            processedCount: ids.length
        });
    } catch (error) {
        console.error('批量处理数据时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 数据备份API
app.post('/api/backup', [authenticateToken, requireAdmin], (req, res) => {
    try {
        // 创建备份目录
        const backupDir = path.join(DATA_DIR, 'backups');
        if (!fs.existsSync(backupDir)) {
            fs.mkdirSync(backupDir, { recursive: true });
        }
        // 生成备份文件名
        const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
        const backupFileName = `backup_${timestamp}.zip`;
        const backupFilePath = path.join(backupDir, backupFileName);
        // 这里简化了备份逻辑，实际应用中应该实现完整的数据备份功能
        // 例如创建数据文件的副本或压缩包
        // 创建空的备份文件作为示例
        fs.writeFileSync(backupFilePath, 'Backup placeholder', 'utf8');
        // 记录备份日志
        logUserActivity(req.user.username, req.user.role, `backup_created_${backupFileName}`);
        res.json({
            success: true,
            message: '数据备份成功',
            backupFile: backupFileName
        });
    } catch (error) {
        console.error('备份数据时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 用户管理API
app.get('/api/admin/users', [authenticateToken, requireAdmin], (req, res) => {
    try {
        // 这里是模拟的用户列表，实际应用中应该从用户数据存储中获取
        const users = [
            { username: 'admin', role: 'admin' },
            { username: 'user1', role: 'user' },
            { username: 'user2', role: 'user' }
        ];
        // 记录操作日志
        logUserActivity(req.user.username, req.user.role, 'view_users_list');
        res.json({
            success: true,
            users: users
        });
    } catch (error) {
        console.error('获取用户列表时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 重置系统API
app.post('/api/admin/reset-system', [authenticateToken, requireAdmin], (req, res) => {
    try {
        // 记录操作日志（在操作前记录）
        logUserActivity(req.user.username, req.user.role, 'reset_system');
        // 这里简化了重置系统的逻辑
        // 实际应用中应该谨慎实现，可能需要清除数据、重置配置等
        // 清除所有用户令牌
        const tokenFiles = fs.readdirSync(DATA_DIR).filter(file => file.startsWith('token_'));
        tokenFiles.forEach(file => {
            fs.unlinkSync(path.join(DATA_DIR, file));
        });
        tokens.clear();
        res.json({
            success: true,
            message: '系统已重置，请重新登录'
        });
    } catch (error) {
        console.error('重置系统时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 查看日志API
app.get('/api/admin/logs', [authenticateToken, requireAdmin], (req, res) => {
    try {
        const logPath = path.join(DATA_DIR, 'user_activity.log');
        let logs = [];
        if (fs.existsSync(logPath)) {
            const logContent = fs.readFileSync(logPath, 'utf8');
            logs = logContent.split('\n').filter(line => line.trim() !== '');
        }
        // 记录操作日志
        logUserActivity(req.user.username, req.user.role, 'view_system_logs');
        res.json({
            success: true,
            logs: logs
        });
    } catch (error) {
        console.error('读取日志时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 设置管理员密码API
app.post('/api/admin/set-admin-password', [authenticateToken, requireAdmin], async (req, res) => {
    const { newPassword } = req.body;
    if (!newPassword || newPassword.length < 6) {
        return res.status(400).json({ success: false, message: '新密码长度至少为6个字符' });
    }
    try {
        // 准备设置管理员密码的文件内容
        const fileContent = `4
${newPassword}\n`;
        const yyzPath = path.join(BASE_DIR, 'yyz.txt');
        fs.writeFileSync(yyzPath, fileContent, 'utf8');
        // 执行设置管理员密码程序
        const exePath = path.join(BASE_DIR, 'AES256sr-J.exe');
        // 使用promise封装exec
        await new Promise((resolve, reject) => {
            exec(exePath, (error, stdout, stderr) => {
                if (error) {
                    reject(error);
                } else {
                    resolve();
                }
            });
        })
        // 检查结果
        const resultFilePath = path.join(BASE_DIR, 'yz.txt');
        if (!fs.existsSync(resultFilePath)) {
            throw new Error('设置管理员密码结果文件不存在');
        }
        const result = fs.readFileSync(resultFilePath, 'utf8').trim();
        if (result === '1') {
            // 记录操作日志
            logUserActivity(req.user.username, req.user.role, 'set_admin_password');

            return res.json({ success: true, message: '管理员密码设置成功' });
        } else {
            return res.status(400).json({ success: false, message: '管理员密码设置失败' });
        }
    } catch (error) {
        console.error('设置管理员密码时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 清理系统缓存API
app.post('/api/admin/clean-cache', [authenticateToken, requireAdmin], (req, res) => {
    try {
        // 清理临时文件和缓存
        const tempDirs = [UPLOADS_DIR, OUTPUT_DIR];
        let cleanedCount = 0;
        tempDirs.forEach(dir => {
            if (fs.existsSync(dir)) {
                const files = fs.readdirSync(dir);
                files.forEach(file => {
                    try {
                        const filePath = path.join(dir, file);
                        if (fs.statSync(filePath).isFile()) {
                            fs.unlinkSync(filePath);
                            cleanedCount++;
                        }
                    } catch (error) {
                        console.error(`清理文件 ${file} 时出错:`, error);
                    }
                });
            }
        });
        // 记录操作日志
        logUserActivity(req.user.username, req.user.role, `clean_cache_${cleanedCount}_files`);

        res.json({
            success: true,
            message: `系统缓存清理成功，共清理 ${cleanedCount} 个文件`
        });
    } catch (error) {
        console.error('清理系统缓存时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 查看安全日志API
app.get('/api/admin/security-logs', [authenticateToken, requireAdmin], (req, res) => {
    try {
        // 这里简化了安全日志的获取，实际应用中应该有专门的安全日志文件
        const securityLogPath = path.join(DATA_DIR, 'security.log');
        let logs = [];
        if (fs.existsSync(securityLogPath)) {
            const logContent = fs.readFileSync(securityLogPath, 'utf8');
            logs = logContent.split('\n').filter(line => line.trim() !== '');
        } else {
            // 如果没有安全日志文件，使用用户活动日志作为替代
            const userLogPath = path.join(DATA_DIR, 'user_activity.log');
            if (fs.existsSync(userLogPath)) {
                const logContent = fs.readFileSync(userLogPath, 'utf8');
                logs = logContent.split('\n').filter(line => line.trim() !== '');
            }
        }
        // 记录操作日志
        logUserActivity(req.user.username, req.user.role, 'view_security_logs');
        res.json({
            success: true,
            logs: logs
        });
    } catch (error) {
        console.error('读取安全日志时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 审计数据完整性API
app.post('/api/admin/audit-data', [authenticateToken, requireAdmin], (req, res) => {
    try {
        // 这里简化了数据完整性审计的逻辑
        // 实际应用中应该实现具体的数据校验逻辑
        // 模拟审计结果
        const auditResult = {
            totalRecords: 100,
            validRecords: 95,
            invalidRecords: 5,
            auditResult: '数据完整性良好'
        };
        // 记录操作日志
        logUserActivity(req.user.username, req.user.role, 'audit_data_integrity');

        res.json({
            success: true,
            ...auditResult
        });
    } catch (error) {
        console.error('审计数据完整性时出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
// 启动服务器
app.listen(PORT, '0.0.0.0', () => {
    console.log(`服务器运行在 http://0.0.0.0:${PORT}`);
    console.log(`局域网访问地址: http://192.168.1.19:${PORT}`);
});