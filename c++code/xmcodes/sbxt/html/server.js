const express = require('express');
const cors = require('cors');
const { createCanvas } = require('canvas');

const app = express();
const PORT = 3001;

// 中间件
app.use(cors());
app.use(express.json({ limit: '10mb' }));

// 固定参数
const SIZE = 50;
const CELL_SIZE = 30;
const CANVAS_SIZE = SIZE * CELL_SIZE; // 1500

// 辅助函数：验证矩阵
function validateMatrix(matrix) {
    if (!Array.isArray(matrix) || matrix.length !== SIZE) return false;
    for (let i = 0; i < SIZE; i++) {
        if (!Array.isArray(matrix[i]) || matrix[i].length !== SIZE) return false;
        for (let j = 0; j < SIZE; j++) {
            const val = matrix[i][j];
            if (val !== 0 && val !== 1) return false;
        }
    }
    return true;
}

// API 端点：生成图片
app.post('/api/generate', (req, res) => {
    const { matrix } = req.body;

    // 验证矩阵
    if (!validateMatrix(matrix)) {
        return res.status(400).json({ error: '无效的矩阵，必须是 50x50 且仅包含 0 或 1' });
    }

    try {
        // 创建画布
        const canvas = createCanvas(CANVAS_SIZE, CANVAS_SIZE);
        const ctx = canvas.getContext('2d');

        // 白色背景
        ctx.fillStyle = '#FFFFFF';
        ctx.fillRect(0, 0, CANVAS_SIZE, CANVAS_SIZE);

        // 绘制黑色格子
        ctx.fillStyle = '#000000';
        for (let i = 0; i < SIZE; i++) {
            for (let j = 0; j < SIZE; j++) {
                if (matrix[i][j] === 1) {
                    ctx.fillRect(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                }
            }
        }

        // 返回 PNG 图片
        const buffer = canvas.toBuffer('image/png');
        res.set('Content-Type', 'image/png');
        res.set('Content-Disposition', 'attachment; filename="matrix.png"');
        res.send(buffer);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: '服务器生成图片失败' });
    }
});

app.listen(PORT, () => {
    console.log(`API 服务已启动: http://localhost:${PORT}`);
});