// 全局变量
let currentData = [];
let currentPage = 1;
const pageSize = 15;
let selectedRows = new Set();
let userRole = 'user'; // 默认为普通用户

// 初始化
document.addEventListener('DOMContentLoaded', function () {
    loadData();
    loadUserInfo();

    // 绑定事件
    document.getElementById('selectAll').addEventListener('change', toggleSelectAll);
    document.getElementById('dataForm').addEventListener('submit', saveData);
    document.getElementById('passwordForm').addEventListener('submit', changePassword);

    // 点击模态框外部关闭
    document.querySelectorAll('.modal').forEach(modal => {
        modal.addEventListener('click', function (e) {
            if (e.target === this) {
                this.style.display = 'none';
            }
        });
    });
});

// 加载用户信息
async function loadUserInfo() {
    const username = localStorage.getItem('username');
    userRole = localStorage.getItem('userRole') || 'user';
    document.getElementById('currentUser').textContent = `欢迎，${username || '用户'}${userRole === 'admin' ? ' (管理员)' : ''}`;

    // 可选：从服务器验证用户状态
    try {
        const response = await fetch('/api/check-auth', {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });
        const result = await response.json();

        if (!result.success) {
            // 如果服务器验证失败，跳回登录页
            logout();
        } else if (result.userRole) {
            // 更新用户角色
            userRole = result.userRole;
            localStorage.setItem('userRole', userRole);
            document.getElementById('currentUser').textContent = `欢迎，${username || '用户'}${userRole === 'admin' ? ' (管理员)' : ''}`;

            // 初始化管理员功能
            if (userRole === 'admin') {
                initAdminFeatures();
            }
        }
    } catch (error) {
        console.error('验证用户状态失败:', error);
    }
}

// 初始化管理员功能
function initAdminFeatures() {
    try {
        // 显示管理员特有的导航项
        const adminSection = document.getElementById('admin-section');
        if (adminSection) adminSection.style.display = 'block';

        // 显示系统设置中的管理员选项
        const adminSettings = document.getElementById('admin-settings');
        if (adminSettings) adminSettings.style.display = 'block';

        // 显示数据管理中的高级操作按钮
        const advancedActions = document.getElementById('advanced-actions');
        if (advancedActions) advancedActions.style.display = 'block';

    } catch (error) {
        console.error('初始化管理员功能时出错:', error);
    }
}

// 检查是否为管理员
function isAdmin() {
    return userRole === 'admin';
}

// 验证管理员权限
function requireAdmin(actionName) {
    if (!isAdmin()) {
        alert(`您没有权限执行${actionName}操作，需要管理员权限`);
        return false;
    }
    return true;
}

// 加载数据
// manualLoad: 是否是用户手动加载数据（如点击加载按钮）
async function loadData(manualLoad = false) {
    try {
        showLoading();

        // 如果是用户手动加载，则直接从服务器加载
        if (manualLoad) {
            console.log('用户手动加载，直接从服务器获取数据...');
        } else {
            // 自动加载时，尝试从本地sj.txt文件加载数据
            try {
                console.log('尝试从本地sj.txt加载数据...');
                const response = await fetch('sj.txt');

                if (response.ok) {
                    const fileContent = await response.text();
                    // 解析数据，按行分割
                    const lines = fileContent.split('\n');
                    currentData = [];

                    // 处理每一行数据，使用逗号分割
                    for (const line of lines) {
                        const trimmedLine = line.trim();
                        if (trimmedLine) { // 跳过空行
                            const parts = trimmedLine.split(',');
                            // 假设数据格式为：序号,姓名,性别,身份证号,出生日期,地点,年龄
                            if (parts.length >= 7) {
                                currentData.push({
                                    序号: parts[0].trim(),
                                    姓名: parts[1].trim(),
                                    性别: parts[2].trim(),
                                    身份证号: parts[3].trim(),
                                    出生日期: parts[4].trim(),
                                    地点: parts[5].trim(),
                                    年龄: parts[6].trim()
                                });
                            }
                        }
                    }

                    console.log('从sj.txt加载数据成功，共', currentData.length, '条');
                    renderTable();
                    updatePaginationInfo(currentData.length);
                    hideLoading();
                    return; // 成功从本地加载，直接返回
                }
            } catch (localError) {
                console.warn('本地加载失败，尝试从服务器加载:', localError);
            }
        }

        // 从服务器加载数据（手动加载或本地加载失败时）
        console.log('从服务器加载数据...');
        const serverResponse = await fetch(`/api/data?page=${currentPage}&pageSize=${pageSize}`, {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });
        const result = await serverResponse.json();

        if (result.success) {
            currentData = result.data;
            renderTable();
            updatePaginationInfo(currentData.length);
            console.log('从服务器加载数据成功，共', currentData.length, '条');
        } else {
            throw new Error('服务器加载失败: ' + result.message);
        }
    } catch (error) {
        console.error('加载数据失败:', error);
        alert('加载数据失败: ' + error.message);
    } finally {
        hideLoading();
    }
}

// 渲染表格
function renderTable() {
    const tbody = document.getElementById('dataTableBody');
    tbody.innerHTML = '';

    // 计算当前页应该显示的数据范围
    const startIndex = (currentPage - 1) * pageSize;
    const endIndex = startIndex + pageSize;
    const currentPageData = currentData.slice(startIndex, endIndex);

    currentPageData.forEach((item, index) => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td><input type="checkbox" class="row-checkbox" value="${item.序号}" onchange="toggleRowSelection('${item.序号}', this.checked)"></td>
            <td>${item.序号}</td>
            <td>${item.姓名}</td>
            <td>${item.性别}</td>
            <td>${item.身份证号}</td>
            <td>${item.出生日期}</td>
            <td>${item.地点}</td>
            <td>${item.年龄}</td>
            <td>
                <button class="btn btn-primary" onclick="editData('${item.序号}')">编辑</button>
                <button class="btn btn-danger" onclick="deleteData('${item.序号}')">删除</button>
                <button class="btn btn-secondary" onclick="khAction('${item.序号}')">KH</button>
            </td>
        `;
        tbody.appendChild(row);
    });
}

// 保存数据到文件
async function saveDataToFile() {
    try {
        showLoading();

        // 准备保存到sj.txt的数据格式
        const dataToSave = currentData.map(item => {
            return [item.序号, item.姓名, item.性别, item.身份证号, item.出生日期, item.地点, item.年龄].join(',');
        }).join('\n');

        // 发送到服务器保存
        const response = await fetch('/api/save-data', {
            method: 'POST',
            headers: {
                'Content-Type': 'text/plain',
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            },
            body: dataToSave
        });

        const result = await response.json();

        if (result.success) {
            alert('数据保存成功');
            console.log('数据已成功保存到sj.txt');
        } else {
            throw new Error('保存失败: ' + result.message);
        }
    } catch (error) {
        console.error('保存数据失败:', error);
        alert('保存数据失败: ' + error.message);
    } finally {
        hideLoading();
    }
}

// 搜索数据
async function searchData() {
    const searchParams = new URLSearchParams();
    
    // 获取所有搜索框的值
    const id = document.getElementById('searchId').value.trim();
    const name = document.getElementById('searchName').value.trim();
    const gender = document.getElementById('searchGender').value.trim();
    const idCard = document.getElementById('searchIdCard').value.trim();
    const birth = document.getElementById('searchBirth').value.trim();
    const location = document.getElementById('searchLocation').value.trim();
    const age = document.getElementById('searchAge').value.trim();
    
    // 调试日志：记录搜索参数
    console.log('搜索参数收集:', {
        id, name, gender, idCard, birth, location, age
    });
    
    // 只有当输入框有值时才添加到搜索参数中
    if (id) searchParams.append('id', id);
    if (name) searchParams.append('name', name);
    if (gender) searchParams.append('gender', gender);
    if (idCard) searchParams.append('idCard', idCard);
    if (birth) searchParams.append('birth', birth);
    if (location) searchParams.append('location', location);
    if (age) searchParams.append('age', age);
    
    // 调试日志：记录最终发送的查询字符串
    console.log('发送的查询字符串:', searchParams.toString());
    
    try {
        showLoading();
        currentPage = 1; // 搜索时重置到第一页

        const response = await fetch(`/api/data?${searchParams.toString()}`, {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });
        const result = await response.json();

        if (result.success) {
            currentData = result.data;
            renderTable();
            updatePaginationInfo(currentData.length);
            console.log('搜索成功，找到', currentData.length, '条结果');
        } else {
            console.error('搜索失败:', result.message);
            alert('搜索失败: ' + result.message);
        }
    } catch (error) {
        console.error('搜索失败:', error);
        alert('搜索失败: 网络错误或服务器问题');
    } finally {
        hideLoading();
    }
}

// 清除搜索
function clearSearch() {
    document.getElementById('searchId').value = '';
    document.getElementById('searchName').value = '';
    document.getElementById('searchGender').value = '';
    document.getElementById('searchIdCard').value = '';
    document.getElementById('searchBirth').value = '';
    document.getElementById('searchLocation').value = '';
    document.getElementById('searchAge').value = '';
    loadData();
}

// 显示添加数据模态框
function showAddModal() {
    document.getElementById('modalTitle').textContent = '添加数据';
    document.getElementById('dataForm').reset();
    document.getElementById('dataModal').style.display = 'block';
}

// 编辑数据
function editData(id) {
    const item = currentData.find(d => d.序号 === id);
    if (item) {
        document.getElementById('modalTitle').textContent = '编辑数据';
        document.getElementById('inputId').value = item.序号;
        document.getElementById('inputName').value = item.姓名;
        document.getElementById('inputGender').value = item.性别;
        document.getElementById('inputIdCard').value = item.身份证号;
        document.getElementById('inputBirth').value = item.出生日期;
        document.getElementById('inputLocation').value = item.地点;
        document.getElementById('inputAge').value = item.年龄;
        document.getElementById('dataModal').style.display = 'block';
    }
}

// 保存数据
async function saveData(event) {
    event.preventDefault();

    const formData = new FormData(event.target);
    const data = Object.fromEntries(formData.entries());

    // 验证必填字段
    if (!data['姓名'] || !data['身份证号'] || !data['序号']) {
        alert('请填写必填字段：序号、姓名、身份证号');
        return;
    }

    // 验证身份证号格式
    const idCardRegex = /^[1-9]\d{5}(18|19|20)\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$/;
    if (!idCardRegex.test(data['身份证号'])) {
        alert('身份证号格式不正确');
        return;
    }

    try {
        const url = document.getElementById('modalTitle').textContent === '添加数据'
            ? '/api/data'
            : `/api/data/${data.序号}`;

        const method = document.getElementById('modalTitle').textContent === '添加数据'
            ? 'POST'
            : 'PUT';

        const response = await fetch(url, {
            method: method,
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            },
            body: JSON.stringify(data)
        });

        const result = await response.json();

        if (result.success) {
            alert('保存成功');
            closeModal('dataModal');
            loadData();
        } else {
            alert('保存失败: ' + result.message);
        }
    } catch (error) {
        console.error('保存失败:', error);
        alert('网络错误：' + error.message);
    }
}

// 删除数据
async function deleteData(id) {
    if (!confirm('确定要删除这条数据吗？')) return;

    try {
        const response = await fetch('/api/data', {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            },
            body: JSON.stringify({ ids: [id] })
        });

        const result = await response.json();

        if (result.success) {
            alert('删除成功');
            loadData();
        } else {
            alert('删除失败: ' + result.message);
        }
    } catch (error) {
        console.error('删除失败:', error);
        alert('网络错误：' + error.message);
    }
}

// 选择行
function toggleRowSelection(id, checked) {
    if (checked) {
        selectedRows.add(id);
    } else {
        selectedRows.delete(id);
    }
    updateSelectAllCheckbox();
}

// 全选/取消全选
function toggleSelectAll() {
    const checkboxes = document.querySelectorAll('.row-checkbox');
    const selectAll = document.getElementById('selectAll').checked;

    checkboxes.forEach(checkbox => {
        checkbox.checked = selectAll;
        toggleRowSelection(checkbox.value, selectAll);
    });
}

function updateSelectAllCheckbox() {
    const checkboxes = document.querySelectorAll('.row-checkbox');
    const selectAll = document.getElementById('selectAll');
    selectAll.checked = checkboxes.length > 0 && selectedRows.size === checkboxes.length;
}

// 删除选中
function deleteSelected() {
    if (selectedRows.size === 0) {
        alert('请先选择要删除的数据');
        return;
    }

    if (!confirm(`确定要删除选中的 ${selectedRows.size} 条数据吗？`)) return;

    // 实现批量删除逻辑
    alert(`批量删除 ${selectedRows.size} 条数据`);
    selectedRows.clear();
    loadData();
}

// 分页功能
function previousPage() {
    if (currentPage > 1) {
        currentPage--;
        loadData();
    }
}

function nextPage() {
    currentPage++;
    loadData();
}

function updatePaginationInfo(total) {
    const totalPages = Math.ceil(total / pageSize);
    document.getElementById('pageInfo').textContent = `第 ${currentPage} 页，共 ${totalPages} 页`;
}

// 显示/隐藏部分
function showSection(sectionId) {
    // 隐藏所有部分
    document.querySelectorAll('.section').forEach(section => {
        section.style.display = 'none';
    });

    // 显示选中的部分
    document.getElementById(sectionId).style.display = 'block';

    // 更新导航激活状态
    document.querySelectorAll('.nav-item').forEach(item => {
        item.classList.remove('active');
    });
    event.target.classList.add('active');

    // 加载特定部分的数据
    if (sectionId === 'data-analysis') {
        loadAnalysis();
    }
}

// 加载分析数据
async function loadAnalysis() {
    try {
        const response = await fetch('/api/data/analysis', {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });
        const result = await response.json();

        if (result.success) {
            renderAnalysis(result.data);
        }
    } catch (error) {
        console.error('加载分析数据失败:', error);
    }
}

function renderAnalysis(data) {
    const content = document.getElementById('analysisContent');

    let html = `
        <div class="chart-container">
            <h3>性别分布</h3>
            <div style="display: flex; gap: 20px; align-items: center;">
                <div style="width: 200px; height: 200px; background: conic-gradient(
                    #4CAF50 0% ${data.gender.男}%, 
                    #2196F3 ${data.gender.男}% 100%
                ); border-radius: 50%;"></div>
                <div>
                    <p>男性: ${data.gender.男}%</p>
                    <p>女性: ${data.gender.女}%</p>
                </div>
            </div>
        </div>
        
        <div class="chart-container">
            <h3>年龄分布</h3>
            <div style="margin-top: 20px;">
    `;

    for (const [group, percent] of Object.entries(data.ageGroups)) {
        html += `
            <div style="margin: 10px 0;">
                <div style="display: flex; justify-content: space-between;">
                    <span>${group}岁</span>
                    <span>${percent}%</span>
                </div>
                <div style="background: #f0f0f0; height: 20px; border-radius: 10px; overflow: hidden;">
                    <div style="background: #FF9800; height: 100%; width: ${percent}%;"></div>
                </div>
            </div>
        `;
    }

    html += `</div></div>`;
    content.innerHTML = html;
}

// 显示公告
async function showNotice() {
    try {
        const response = await fetch('/api/notice', {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });
        const result = await response.json();

        if (result.success) {
            document.getElementById('noticeContent').textContent = result.data;
            document.getElementById('noticeModal').style.display = 'block';
        }
    } catch (error) {
        console.error('加载公告失败:', error);
    }
}

// 修改密码
function showChangePasswordModal() {
    document.getElementById('passwordForm').reset();
    document.getElementById('passwordModal').style.display = 'block';
}

async function changePassword(event) {
    event.preventDefault();

    const newPassword = document.getElementById('newPassword').value;
    const confirmPassword = document.getElementById('confirmPassword').value;

    if (newPassword !== confirmPassword) {
        alert('两次输入的新密码不一致');
        return;
    }

    try {
        const response = await fetch('/api/change-password', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            },
            body: JSON.stringify({ newPassword, confirmPassword })
        });

        const result = await response.json();

        if (result.success) {
            alert('密码修改成功');
            closeModal('passwordModal');
        } else {
            alert('密码修改失败: ' + result.message);
        }
    } catch (error) {
        console.error('修改密码失败:', error);
        alert('网络错误');
    }
}

// KH功能
async function khAction(personId) {
    if (!confirm('确定执行KH操作吗？')) return;

    try {
        const response = await fetch('/api/kh', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            },
            body: JSON.stringify({ personId, format: '1' })
        });

        const result = await response.json();

        if (result.success) {
            alert('KH操作完成');
        } else {
            alert('KH操作失败: ' + result.message);
        }
    } catch (error) {
        console.error('KH操作失败:', error);
        alert('网络错误');
    }
}

// 导入数据
async function importData() {
    try {
        // 创建一个文件选择对话框
        const input = document.createElement('input');
        input.type = 'file';
        input.accept = '.csv,.txt';

        input.onchange = async (event) => {
            const file = event.target.files[0];
            if (!file) return;

            try {
                showLoading();

                // 使用FormData上传文件
                const formData = new FormData();
                formData.append('file', file);

                const response = await fetch('/api/import-data', {
                    method: 'POST',
                    headers: {
                        'Authorization': 'Bearer ' + localStorage.getItem('token')
                    },
                    body: formData
                });

                const result = await response.json();

                if (result.success) {
                    alert('数据导入成功');
                    loadData(); // 重新加载数据
                } else {
                    alert('数据导入失败: ' + result.message);
                }
            } catch (error) {
                console.error('导入数据失败:', error);
                alert('导入数据时发生错误: ' + error.message);
            } finally {
                hideLoading();
            }
        };

        input.click();
    } catch (error) {
        console.error('导入功能错误:', error);
        alert('导入功能不可用: ' + error.message);
    }
}

// 导出数据
async function exportData() {
    try {
        showLoading();

        const response = await fetch('/api/export-data', {
            method: 'GET',
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        if (response.ok) {
            // 获取文件名
            const contentDisposition = response.headers.get('content-disposition');
            let fileName = 'data_export.csv';
            if (contentDisposition) {
                const match = contentDisposition.match(/filename="?([^"]+)"?/);
                if (match && match[1]) {
                    fileName = match[1];
                }
            }

            // 创建一个下载链接
            const blob = await response.blob();
            const url = window.URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.style.display = 'none';
            a.href = url;
            a.download = fileName;
            document.body.appendChild(a);
            a.click();

            // 清理
            window.URL.revokeObjectURL(url);
            document.body.removeChild(a);

            console.log('数据导出成功');
        } else {
            const result = await response.json();
            throw new Error(result.message || '导出失败');
        }
    } catch (error) {
        console.error('导出数据失败:', error);
        alert('导出数据失败: ' + error.message);
    } finally {
        hideLoading();
    }
}

// 整理数据
function cleanData() {
    alert('整理数据功能待实现');
}

// 关闭模态框
function closeModal(modalId) {
    document.getElementById(modalId).style.display = 'none';
}

// 显示加载状态
function showLoading() {
    // 简单的加载提示
    const loading = document.createElement('div');
    loading.id = 'globalLoading';
    loading.innerHTML = '加载中...';
    loading.style.cssText = `
        position: fixed;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
        background: rgba(0,0,0,0.8);
        color: white;
        padding: 20px;
        border-radius: 8px;
        z-index: 9999;
    `;
    document.body.appendChild(loading);
}

function hideLoading() {
    const loading = document.getElementById('globalLoading');
    if (loading) {
        loading.remove();
    }
}

// 管理员特有功能

// 批量处理
async function batchProcess() {
    if (!requireAdmin('批量处理')) return;

    if (selectedRows.size === 0) {
        alert('请先选择要处理的数据');
        return;
    }

    try {
        showLoading();
        const response = await fetch('/api/batch-process', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            },
            body: JSON.stringify({ ids: Array.from(selectedRows) })
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            alert(`批量处理成功，共处理 ${result.processedCount} 条数据`);
            selectedRows.clear();
            loadData();
        } else {
            alert('批量处理失败: ' + result.message);
        }
    } catch (error) {
        console.error('批量处理失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 备份数据
async function backupData() {
    if (!requireAdmin('备份数据')) return;

    try {
        showLoading();
        const response = await fetch('/api/backup', {
            method: 'POST',
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            alert('数据备份成功，备份文件: ' + result.backupFile);
        } else {
            alert('数据备份失败: ' + result.message);
        }
    } catch (error) {
        console.error('备份数据失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 用户管理
async function manageUsers() {
    if (!requireAdmin('用户管理')) return;

    try {
        showLoading();
        const response = await fetch('/api/admin/users', {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            // 这里可以显示用户管理界面
            let userListHtml = '用户列表：\n';
            result.users.forEach(user => {
                userListHtml += `用户名: ${user.username}, 角色: ${user.role}\n`;
            });
            alert(userListHtml);
        } else {
            alert('加载用户列表失败: ' + result.message);
        }
    } catch (error) {
        console.error('加载用户列表失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 重置系统
async function resetSystem() {
    alert('别瞎78乱点！还想重置系统？自己去数据库删数据吧！');
    /*if (!requireAdmin('重置系统')) return;

    if (!confirm('警告：重置系统将清除所有数据，确定要继续吗？')) return;

    try {
        showLoading();
        const response = await fetch('/api/admin/reset-system', {
            method: 'POST',
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            alert('系统重置成功');
            logout();
        } else {
            alert('系统重置失败: ' + result.message);
        }
    } catch (error) {
        console.error('重置系统失败:', error);
        hideLoading();
        alert('网络错误');
    }
    */
}

// 查看日志
async function viewLogs() {
    if (!requireAdmin('查看日志')) return;

    try {
        showLoading();
        const response = await fetch('/api/admin/logs', {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            // 简单显示日志内容
            const logContent = result.logs.slice(0, 1000).join('\n'); // 限制显示长度
            alert('系统日志：\n' + logContent);
        } else {
            alert('加载日志失败: ' + result.message);
        }
    } catch (error) {
        console.error('加载日志失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 设置管理员密码
async function setAdminPassword() {
    alert('都是管理员了，自己去数据库改密码吧！');
    // if (!requireAdmin('设置管理员密码')) return;

    // const newPassword = prompt('请输入新的管理员密码（长度至少6位）:');
    // if (!newPassword || newPassword.length < 6) {
    //     alert('密码不符合要求');
    //     return;
    // }

    // const confirmPassword = prompt('请再次输入新的管理员密码:');
    // if (newPassword !== confirmPassword) {
    //     alert('两次输入的密码不一致');
    //     return;
    // }

    // try {
    //     showLoading();
    //     const response = await fetch('/api/admin/set-admin-password', {
    //         method: 'POST',
    //         headers: {
    //             'Content-Type': 'application/json',
    //             'Authorization': 'Bearer ' + localStorage.getItem('token')
    //         },
    //         body: JSON.stringify({ newPassword })
    //     });

    //     const result = await response.json();
    //     hideLoading();

    //     if (result.success) {
    //         alert('管理员密码设置成功');
    //     } else {
    //         alert('管理员密码设置失败: ' + result.message);
    //     }
    // } catch (error) {
    //     console.error('设置管理员密码失败:', error);
    //     hideLoading();
    //     alert('网络错误');
    // }
}

// 清理系统缓存
async function cleanSystem() {
    if (!requireAdmin('清理系统缓存')) return;

    if (!confirm('确定要清理系统缓存吗？')) return;

    try {
        showLoading();
        const response = await fetch('/api/admin/clean-cache', {
            method: 'POST',
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            alert('系统缓存清理成功');
        } else {
            alert('系统缓存清理失败: ' + result.message);
        }
    } catch (error) {
        console.error('清理系统缓存失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 查看安全日志
async function viewSecurityLogs() {
    if (!requireAdmin('查看安全日志')) return;

    try {
        showLoading();
        const response = await fetch('/api/admin/security-logs', {
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            // 简单显示安全日志内容
            const logContent = result.logs.slice(0, 1000).join('\n'); // 限制显示长度
            alert('安全日志：\n' + logContent);
        } else {
            alert('加载安全日志失败: ' + result.message);
        }
    } catch (error) {
        console.error('加载安全日志失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 审计数据完整性
async function auditData() {
    if (!requireAdmin('审计数据完整性')) return;

    try {
        showLoading();
        const response = await fetch('/api/admin/audit-data', {
            method: 'POST',
            headers: {
                'Authorization': 'Bearer ' + localStorage.getItem('token')
            }
        });

        const result = await response.json();
        hideLoading();

        if (result.success) {
            alert('数据完整性审计完成\n' +
                `总记录数: ${result.totalRecords}\n` +
                `完整记录: ${result.validRecords}\n` +
                `异常记录: ${result.invalidRecords}\n` +
                `审计结果: ${result.auditResult}`);
        } else {
            alert('数据完整性审计失败: ' + result.message);
        }
    } catch (error) {
        console.error('审计数据完整性失败:', error);
        hideLoading();
        alert('网络错误');
    }
}

// 退出登录
async function logout() {
    if (confirm('确定要退出登录吗？')) {
        try {
            // 调用退出API（如果有的话）
            await fetch('/api/logout', {
                method: 'POST',
                headers: {
                    'Authorization': 'Bearer ' + localStorage.getItem('token')
                }
            });
        } catch (error) {
            console.error('退出请求失败:', error);
        } finally {
            // 清除本地存储
            localStorage.removeItem('isLoggedIn');
            localStorage.removeItem('username');
            localStorage.removeItem('token');
            localStorage.removeItem('userRole');

            // 跳转到登录页
            window.location.href = 'index.html';
        }
    }
}