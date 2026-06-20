const express = require('express');
const http = require('http');
const path = require('path');
const cors = require('cors');

const app = express();
const server = http.createServer(app);

// 配置 - 使用端口3002
const PORT = 3002;
const GRID_SIZE = { rows: 800, cols: 1600 };

// 存储颜色状态的二维数组
let colorGrid = Array(GRID_SIZE.rows).fill().map(() => 
    Array(GRID_SIZE.cols).fill('#ffffff')
);

// 中间件
app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

// API 路由
app.post('/api/setColor', (req, res) => {
    try {
        const { x, y, k } = req.body;
        
        // 验证参数
        if (x === undefined || y === undefined || k === undefined) {
            return res.status(400).json({ 
                success: false, 
                error: 'Missing parameters. Required: x, y, k' 
            });
        }
        
        // 验证坐标范围
        if (x < 0 || x >= GRID_SIZE.rows || y < 0 || y >= GRID_SIZE.cols) {
            return res.status(400).json({ 
                success: false, 
                error: `Coordinates out of range. x: 0-${GRID_SIZE.rows-1}, y: 0-${GRID_SIZE.cols-1}` 
            });
        }
        
        // 验证颜色格式
        const hexColorRegex = /^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$/;
        if (!hexColorRegex.test(k)) {
            return res.status(400).json({ 
                success: false, 
                error: 'Invalid color format. Use HEX format (e.g., #ff0000 or #f00)' 
            });
        }
        
        // 确保颜色是6位HEX格式
        let color = k;
        if (k.length === 4) {
            color = '#' + k[1] + k[1] + k[2] + k[2] + k[3] + k[3];
        }
        
        // 设置颜色
        colorGrid[x][y] = color;
        
        res.json({
            success: true,
            data: { x, y, color }
        });
    } catch (error) {
        res.status(500).json({ 
            success: false, 
            error: 'Server error: ' + error.message 
        });
    }
});

app.get('/api/getColors', (req, res) => {
    try {
        // 可以选择返回整个网格或部分网格
        const { x, y, width, height } = req.query;
        
        if (x && y && width && height) {
            // 返回指定区域的颜色
            const startX = parseInt(x);
            const startY = parseInt(y);
            const w = parseInt(width);
            const h = parseInt(height);
            
            if (startX >= 0 && startY >= 0 && w > 0 && h > 0) {
                const endX = Math.min(startX + h - 1, GRID_SIZE.rows - 1);
                const endY = Math.min(startY + w - 1, GRID_SIZE.cols - 1);
                
                const region = [];
                for (let i = startX; i <= endX; i++) {
                    region.push(colorGrid[i].slice(startY, endY + 1));
                }
                
                return res.json({
                    success: true,
                    data: {
                        region,
                        startX,
                        startY,
                        endX,
                        endY
                    }
                });
            }
        }
        
        // 默认返回整个网格
        res.json({
            success: true,
            data: {
                grid: colorGrid,
                size: GRID_SIZE
            }
        });
    } catch (error) {
        res.status(500).json({ 
            success: false, 
            error: 'Server error: ' + error.message 
        });
    }
});

// 前端页面
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index_simple.html'));
});

// 启动服务器
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
    console.log(`Grid size: ${GRID_SIZE.rows}x${GRID_SIZE.cols}`);
    console.log(`API endpoints:`);
    console.log(`  POST /api/setColor - Set color of a cell`);
    console.log(`  GET /api/getColors - Get grid colors`);
    console.log(`  GET / - Frontend interface`);
});

module.exports = app;