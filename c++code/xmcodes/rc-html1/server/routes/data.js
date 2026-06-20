const express = require('express');
const multer = require('multer');
const { Op } = require('sequelize');
const path = require('path');
const fs = require('fs');
const Person = require('../models/Person');
const { auth } = require('../middlewares/auth');

const router = express.Router();

// 设置文件上传存储
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    const dir = path.join(__dirname, '../../public/uploads');
    if (!fs.existsSync(dir)) {
      fs.mkdirSync(dir, { recursive: true });
    }
    cb(null, dir);
  },
  filename: function (req, file, cb) {
    cb(null, Date.now() + '-' + file.originalname);
  }
});

const upload = multer({ storage });

// 获取所有数据
router.get('/persons', auth, async (req, res) => {
  try {
    const { search, page = 1, limit = 10, order = '编号:asc' } = req.query;
    const offset = (page - 1) * limit;

    // 解析排序参数
    const [orderField, orderDirection] = order.split(':');
    const orderOptions = [[orderField || '编号', orderDirection || 'asc']];

    let where = {};
    if (search) {
      where = {
        [Op.or]: [
          { '编号': { [Op.like]: `%${search}%` } },
          { '姓名': { [Op.like]: `%${search}%` } },
          { '身份证号': { [Op.like]: `%${search}%` } },
          { '工作单位': { [Op.like]: `%${search}%` } },
          { '联系电话': { [Op.like]: `%${search}%` } }
        ]
      };
    }

    const { count, rows } = await Person.findAndCountAll({
      where,
      offset,
      limit: parseInt(limit),
      order: orderOptions
    });

    res.json({ data: rows, total: count, page: parseInt(page), limit: parseInt(limit) });
  } catch (error) {
    res.status(500).json({ error: '获取数据失败', message: error.message });
  }
});

// 添加单条数据
router.post('/persons', auth, async (req, res) => {
  try {
    const person = await Person.create(req.body);
    res.status(201).json(person);
  } catch (error) {
    res.status(500).json({ error: '添加数据失败', message: error.message });
  }
});

// 获取单个数据
router.get('/persons/:id', auth, async (req, res) => {
  try {
    const person = await Person.findByPk(req.params.id);
    if (!person) {
      return res.status(404).json({ error: '数据不存在' });
    }

    res.json(person);
  } catch (error) {
    res.status(500).json({ error: '获取数据失败', message: error.message });
  }
});

// 更新数据
router.put('/persons/:id', auth, async (req, res) => {
  try {
    const person = await Person.findByPk(req.params.id);
    if (!person) {
      return res.status(404).json({ error: '数据不存在' });
    }

    await person.update(req.body);
    res.json(person);
  } catch (error) {
    res.status(500).json({ error: '更新数据失败', message: error.message });
  }
});

// 删除单条数据
router.delete('/persons/:id', auth, async (req, res) => {
  try {
    const person = await Person.findByPk(req.params.id);
    if (!person) {
      return res.status(404).json({ error: '数据不存在' });
    }

    await person.destroy();
    res.json({ message: '删除数据成功' });
  } catch (error) {
    res.status(500).json({ error: '删除数据失败', message: error.message });
  }
});

// 批量删除数据
router.delete('/persons', auth, async (req, res) => {
  try {
    const { ids } = req.body;
    if (!ids || !Array.isArray(ids)) {
      return res.status(400).json({ error: '请提供要删除的数据ID列表' });
    }

    await Person.destroy({ where: { id: ids } });
    res.json({ message: '批量删除数据成功' });
  } catch (error) {
    res.status(500).json({ error: '批量删除数据失败', message: error.message });
  }
});

// 导入数据
router.post('/import', auth, upload.single('file'), async (req, res) => {
  try {
    if (!req.file) {
      return res.status(400).json({ error: '请选择要导入的文件' });
    }

    console.log('开始导入文件:', req.file.originalname);
    console.log('文件路径:', req.file.path);
    console.log('文件大小:', req.file.size, '字节');

    // 读取文件，使用utf8编码确保中文正确解析
    const fileContent = fs.readFileSync(req.file.path, 'utf8');
    console.log('文件内容长度:', fileContent.length, '字符');

    // 检查文件内容
    if (!fileContent) {
      return res.status(400).json({ error: '文件内容为空' });
    }

    // CSV解析逻辑
    const lines = fileContent.split('\n').filter(line => line.trim());
    console.log('有效行数量:', lines.length);

    if (lines.length < 1) {
      return res.status(400).json({ error: '文件没有有效数据行' });
    }

    // 获取CSV头
    const headerLine = lines[0].trim();
    console.log('CSV头:', headerLine);
    const headers = headerLine.split(',').map(header => header.trim());
    console.log('解析后的头字段:', headers);

    const data = [];

    for (let i = 1; i < lines.length; i++) {
      const line = lines[i].trim();
      console.log(`处理第${i}行:`, line);

      // 跳过空行
      if (!line) {
        console.log(`跳过空行: ${i}`);
        continue;
      }

      // 使用正则表达式解析CSV行，支持引号内的逗号
      const values = [];
      let current = '';
      let inQuotes = false;

      for (let j = 0; j < line.length; j++) {
        const char = line[j];
        if (char === '"') {
          inQuotes = !inQuotes;
        } else if (char === ',' && !inQuotes) {
          values.push(current.trim());
          current = '';
        } else {
          current += char;
        }
      }
      values.push(current.trim());

      console.log(`解析后的值:`, values);

      // 字段映射：将CSV字段映射到模型字段
      const csvData = {};
      headers.forEach((header, index) => {
        csvData[header] = values[index] || '';
        console.log(`字段映射: ${header} = ${csvData[header]}`);
      });

      // 转换为模型字段
      const row = {};

      // 映射字段
      row['编号'] = csvData['序号'] || '';
      row['姓名'] = csvData['姓名'] || '';
      row['性别'] = csvData['性别'] || '未知';

      // 转换出生日期格式
      if (csvData['出生日期']) {
        try {
          // 处理不同的日期格式
          let dateStr = csvData['出生日期'];
          // 替换所有可能的日期分隔符
          dateStr = dateStr.replace(/\//g, '-').replace(/\./g, '-');
          console.log(`处理日期: ${csvData['出生日期']} -> ${dateStr}`);

          const date = new Date(dateStr);
          if (!isNaN(date.getTime())) {
            row['出生年月'] = date;
            console.log(`转换后的日期:`, date);
          } else {
            console.error(`日期转换失败: ${csvData['出生日期']}`);
            row['出生年月'] = new Date();
          }
        } catch (e) {
          console.error(`日期转换异常: ${csvData['出生日期']}`, e);
          row['出生年月'] = new Date();
        }
      } else {
        row['出生年月'] = new Date();
      }

      row['身份证号'] = csvData['身份证号'] || '';
      row['民族'] = '汉'; // 默认值
      row['政治面貌'] = '群众'; // 默认值
      row['学历'] = '小学'; // 默认值
      row['学位'] = '无'; // 默认值
      row['毕业院校'] = '未知'; // 默认值
      row['专业'] = '未知'; // 默认值
      row['毕业时间'] = new Date(); // 默认值
      row['工作单位'] = '未知'; // 默认值
      row['职务'] = '无'; // 默认值
      row['职称'] = '无'; // 默认值
      row['联系电话'] = '无'; // 默认值
      row['电子邮箱'] = '无'; // 默认值
      row['通讯地址'] = csvData['地点'] || '无'; // 映射地点到通讯地址
      row['邮编'] = '000000'; // 默认值
      row['参加工作时间'] = new Date(); // 默认值

      console.log(`生成的数据行:`, row);
      data.push(row);
    }

    console.log(`准备导入的数据数量:`, data.length);

    if (data.length === 0) {
      return res.status(400).json({ error: '没有可导入的数据' });
    }

    // 批量创建数据，添加更多选项
    const result = await Person.bulkCreate(data, {
      returning: true,
      validate: true,
      individualHooks: true
    });

    console.log(`导入成功，实际导入数量:`, result.length);

    // 删除临时文件
    fs.unlinkSync(req.file.path);
    console.log(`临时文件已删除:`, req.file.path);

    res.json({
      message: '数据导入成功',
      count: result.length,
      originalCount: data.length,
      fileName: req.file.originalname
    });
  } catch (error) {
    console.error('数据导入失败详细信息:', error);

    // 尝试删除临时文件
    try {
      if (req.file && req.file.path) {
        fs.unlinkSync(req.file.path);
        console.log(`临时文件已删除:`, req.file.path);
      }
    } catch (unlinkError) {
      console.error('删除临时文件失败:', unlinkError);
    }

    res.status(500).json({
      error: '数据导入失败',
      message: error.message,
      fileName: req.file?.originalname,
      code: error.name,
      stack: process.env.NODE_ENV === 'production' ? undefined : error.stack
    });
  }
});

// 导出数据
router.get('/export', auth, async (req, res) => {
  try {
    const persons = await Person.findAll();
    if (persons.length === 0) {
      return res.status(404).json({ error: '没有数据可导出' });
    }

    // 生成CSV
    const headers = Object.keys(persons[0].dataValues).filter(key => key !== 'id' && key !== 'createdAt' && key !== 'updatedAt');
    const csvContent = [headers.join(',')];

    persons.forEach(person => {
      const row = headers.map(header => person[header] || '');
      csvContent.push(row.join(','));
    });

    res.setHeader('Content-Disposition', 'attachment; filename=data.csv');
    res.setHeader('Content-Type', 'text/csv');
    res.send(csvContent.join('\n'));
  } catch (error) {
    res.status(500).json({ error: '数据导出失败', message: error.message });
  }
});

// KH功能
router.post('/kh', auth, async (req, res) => {
  try {
    const { data } = req.body;

    // 这里实现KH功能的逻辑，根据实际需求调整
    // 示例：将数据存储到文件
    const khFilePath = path.join(__dirname, '../../public/output/kh.txt');
    const dir = path.dirname(khFilePath);
    if (!fs.existsSync(dir)) {
      fs.mkdirSync(dir, { recursive: true });
    }

    fs.writeFileSync(khFilePath, JSON.stringify(data, null, 2), 'utf8');

    res.json({ message: 'KH功能执行成功' });
  } catch (error) {
    res.status(500).json({ error: 'KH功能执行失败', message: error.message });
  }
});

// 从服务器加载数据（示例）
router.get('/load-from-server', auth, async (req, res) => {
  try {
    // 这里可以实现从其他数据源加载数据的逻辑
    const persons = await Person.findAll();
    res.json({ data: persons, message: '从服务器加载数据成功' });
  } catch (error) {
    res.status(500).json({ error: '从服务器加载数据失败', message: error.message });
  }
});

// 保存当前数据到服务器（示例）
router.post('/save-to-server', auth, async (req, res) => {
  try {
    const { data } = req.body;
    if (!data || !Array.isArray(data)) {
      return res.status(400).json({ error: '请提供要保存的数据' });
    }

    // 这里可以实现保存数据到其他数据源的逻辑
    // 示例：保存到数据库（如果需要）
    res.json({ message: '保存当前数据到服务器成功' });
  } catch (error) {
    res.status(500).json({ error: '保存当前数据到服务器失败', message: error.message });
  }
});

module.exports = router;