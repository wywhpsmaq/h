const express = require('express');
const fs = require('fs');
const { exec } = require('child_process');
const path = require('path');
const cors = require('cors');
const app = express();
const PORT = 3000;
app.use(express.json());
app.use(cors());
app.use(express.static('public'));
app.post('/api/login', (req, res) => {
    const { username, password } = req.body;
    if (!username || !password) {
        return res.status(400).json({ success: false, message: '用户名和密码不能为空' });
    }
    console.log('收到登录请求:', { username, password });
    try {
        const fileContent = `1\n${username}\n${password}\n`;
        fs.writeFileSync('yyz.txt', fileContent, 'utf8');
        console.log('正在准备验证');
        const exePath = path.join(__dirname, 'AES256-Z.exe');
        console.log('正在验证:', exePath);
        exec(exePath, (error, stdout, stderr) => {
            if (error) {
                console.error('执行程序出错:', error);
                return res.status(500).json({ success: false, message: '程序执行失败: ' + error.message });
            }
            console.log('验证完成');
            try {
                const resultFilePath = path.join(__dirname, 'yz.txt');
                if (!fs.existsSync(resultFilePath)) {
                    console.error('验证结果出错');
                    return res.status(500).json({ success: false, message: '结果不存在' });
                }
                const result = fs.readFileSync(resultFilePath, 'utf8').trim();
                console.log('结果:', result);
                if (result === '1') {
                    res.json({ success: true, message: '登录成功！' });
                } else {
                    res.json({ success: false, message: '登录失败！' });
                }
            } catch (readError) {
                console.error('读取失败:', readError);
                res.status(500).json({ success: false, message: '读取结果失败: ' + readError.message });
            }
        });
    } catch (error) {
        console.error('处理过程中出错:', error);
        res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    }
});
app.post('/api/register', (req, res) => {
    // const { username, password, confirmPassword } = req.body;
    // if (!username || !password || !confirmPassword) {
    //     return res.status(400).json({ success: false, message: '所有字段都不能为空' });
    // }
    // if (password !== confirmPassword) {
    //     return res.status(400).json({ success: false, message: '两次输入的密码不一致' });
    // }
    // if (password.length < 6) {
    //     return res.status(400).json({ success: false, message: '密码长度至少为6个字符' });
    // }
    // console.log('收到注册请求:', { username, password });
    // try {
    //     const fileContent = `0\n${username}\n${password}\n`;
    //     fs.writeFileSync('yyz.txt', fileContent, 'utf8');
    //     console.log('正在准备验证');
    //     const exePath = path.join(__dirname, 'AES256-Z.exe');
    //     console.log('正在验证:', exePath);
    //     exec(exePath, (error, stdout, stderr) => {
    //         if (error) {
    //             console.error('执行程序出错:', error);
    //             return res.status(500).json({ success: false, message: '程序执行失败: ' + error.message });
    //         }
    //         console.log('验证完成');
    //         try {
    //             const resultFilePath = path.join(__dirname, 'yz.txt');
    //             if (!fs.existsSync(resultFilePath)) {
    //                 console.error('结果不存在');
    //                 return res.status(500).json({ success: false, message: '结果不存在' });
    //             }
    //             const result = fs.readFileSync(resultFilePath, 'utf8').trim();
    //             console.log('结果:', result);
    //             if (result === '1') {
    //                 res.json({ success: true, message: '注册成功！' });
    //             } else {
    //                 res.json({ success: false, message: '注册失败！' });
    //             }
    //         } catch (readError) {
    //             console.error('读取失败:', readError);
    //             res.status(500).json({ success: false, message: '读取结果失败: ' + readError.message });
    //         }
    //     });
    // } catch (error) {
    //     console.error('处理过程中出错:', error);
    //     res.status(500).json({ success: false, message: '服务器内部错误: ' + error.message });
    // }
});
app.listen(PORT, '0.0.0.0', () => {
    console.log(`服务器运行在 http://0.0.0.0:${PORT}`);
    console.log(`局域网访问地址: http://YOUR_IP_ADDRESS:${PORT}`);
});